/* Logan Current, Project 3, this file creates a doubly linked list and has the following methods available to it: 
    push- add to the very end
    pop- takes the very last node off
    insert- insert 1 node anywhere in the sequence
    front- show what element the head is 
    back- show what element the tail is 
    empty- see if the list is empty
    clear- empties the whole list 
    size- returns the size of the list 
    erase- delete what node and how many (including itself) in front of it

    The following operators:
    << will allow the whole list to be printed
    = copies the list to another list 
    [] see what element is at that position
*/

#include "Sequence.h"

Sequence::Sequence(size_type sz)
{
    //constructor
    numElts = 0;
    head = nullptr;
    tail = nullptr;
    //makes the initilized list of the desired size
    for (int i = 0; i < sz; i++)
    {
        push_back(0);
    }
}

Sequence::Sequence(const Sequence &s)
{
    //makes a *deep* copy of the sequence
    numElts = 0;
    head = nullptr;
    tail = nullptr;
    SequenceNode *toCopy = s.head;
    while (toCopy != nullptr)
    {
        push_back(toCopy->elt);
        toCopy = toCopy->next;
    }
}

Sequence::~Sequence()
{
    //calls clear
    clear();
}

Sequence &Sequence::operator=(const Sequence &s)
{
    //remake the sequence to equal the desired one
    clear();
    head = nullptr;
    tail = nullptr;
    numElts = 0;
    SequenceNode *toCopy = s.head;
    while (toCopy != nullptr)
    {
        push_back(toCopy->elt);
        toCopy = toCopy->next;
    }
    return *this;
}

Sequence::value_type &Sequence::operator[](size_type position)
{
    //cant call a position outside the list or if the list is empty
    if (position < 0 || position > numElts || numElts == 0)
    {
        throw exception();
    }
    else
    {
        SequenceNode *toFind = head;
        //iterates thru the list and returns the desired element
        for (int i = 0; i < numElts; i++)
        {
            if (position == i)
            {
                return toFind->elt;
            }
            toFind = toFind->next;
        }
    }
}

void Sequence::push_back(const value_type &value)
{
    //if this is the first node in the list
    if (head == nullptr)
    {
        SequenceNode *newNode = new SequenceNode(value);
        head = newNode;
        head->prev = nullptr;
        head->next = nullptr;
        tail = newNode;
        numElts++;
    }
    //just add another one and make it the new tail
    else
    {
        SequenceNode *newNode = new SequenceNode(value);
        newNode->next = nullptr;
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        numElts++;
    }
}

void Sequence::pop_back()
{
    //can't empty an empty list
    if (head == nullptr)
    {
        throw exception();
    }
    SequenceNode *deleteME = tail;
    //just remove the one and make it an empty list
    if (numElts == 1)
    {
        delete deleteME;
        head = nullptr;
        tail = nullptr;
        numElts = 0;
    }
    else
    {
        //remove it
        tail = tail->prev;
        tail->next = nullptr;
        delete deleteME;
        numElts--;
        if (numElts == 0)
        {
            head = nullptr;
        }
    }
}

void Sequence::insert(size_type position, value_type value)
{
    //can't add something that is greater than the size of the list
    if (position > numElts)
    {
        throw exception();
    }
    //just push back
    if (position == numElts)
    {
        push_back(value);
    }
    //adding only to the head
    else if (position == 0)
    {
        SequenceNode *nodeToAdd = new SequenceNode(value);
        nodeToAdd = head->next;
        nodeToAdd->prev = head;
        nodeToAdd->next = nullptr;
        head = nodeToAdd;
    }
    else
    {
        //point to front and back of the position and have them point to the new node
        SequenceNode *nodeToAdd = new SequenceNode(value);
        SequenceNode *currentNode = head;
        SequenceNode *frontKeep = nullptr;
        SequenceNode *endKeep = nullptr;
        //same process as erase
        for (int i = 0; i <= numElts; i++)
        {
            if(position == i){
                frontKeep = currentNode->prev;
                endKeep = currentNode->next;
            }
            if(currentNode->next != nullptr)
            {
                currentNode = currentNode->next;
            }
            
        }
        //sets the new node pointers
        frontKeep ->next = nodeToAdd;
        nodeToAdd->prev = frontKeep;
        endKeep->prev = nodeToAdd;
        nodeToAdd->next = endKeep;
        numElts++;
    }
}

const Sequence::value_type &Sequence::front() const
{
    //returns the head if there is an element there
    if (head == nullptr)
    {
        throw exception();
    }
    return head->elt;
}

const Sequence::value_type &Sequence::back() const
{
    //returns the tail if there is an element there
    if (tail == nullptr)
    {
        throw exception();
    }
    return tail->elt;
}

bool Sequence::empty() const
{
    //checks if the list is empty
    if (numElts == 0)
    {
        return true;
    }
    return false;
}

Sequence::size_type Sequence::size() const
{
    //return the size
    return numElts;
}

void Sequence::clear()
{
    // clears the entire list
    if (head != nullptr)
    {
        SequenceNode *kill = head;
        while (kill != nullptr)
        {
            //readies the next node to kill then kills it until it's null
            SequenceNode *killNext = kill->next;
            delete kill;
            kill = killNext;
        }
    }
    head = nullptr;
    tail = nullptr;
    numElts = 0;
}

void Sequence::erase(size_type position, size_type count)
{

    SequenceNode *frontKeep = nullptr;
    SequenceNode *endKeep = nullptr;
    //if they just wanted to get rid of the last node ONLY
    if (position == numElts && count >= 1)
    {
        pop_back();
    }
    //is more than what the list can do 
    else if ((position + count) > numElts)
    {
        throw exception();
    }
    else
    {
        //is a valid position 
        SequenceNode *toFind = head;
        for (int i = 0; i <= position; i++)
        {
            if (i == position)
            {
                frontKeep = toFind->prev;
            }
            else
            {
                toFind = toFind->next;
            }
        }
        //puts the endkeep at frontkeep then iterates thru the list until it gets to one past the last one to kill
        if (position > 0)
        {
            endKeep = frontKeep;
            for (int i = 0; i < (count + 1); i++)
            {
                endKeep = endKeep->next;
            }
        }
        //if they want to start at the head
        else if (position == 0)
        {
            endKeep = head;
            for (int i = 0; i < count; i++)
            {
                endKeep = endKeep->next;
            }
        }
        SequenceNode *kill = nullptr;
        //as long as it's not head or starting there then frontKeep kill next
        if (position > 0)
        {
            kill = frontKeep->next;
        }
        //
        else
        {
            kill = head;
        }
        //kill process, similar to clear()
        while (kill != endKeep)
        {
            SequenceNode *killNext = kill->next;
            delete kill;
            kill = killNext;
            numElts--;
        }
        //reset the end as the new head if it was the starting position was 0 (start of list)
        if (position == 0)
        {
            head = endKeep;
            head->prev = nullptr;
        }
        //every other case
        else
        {
            frontKeep->next = endKeep;
            //every other case where endKeep isn't null
            if (endKeep != nullptr)
            {
                endKeep->prev = frontKeep;
            }
            else
            {
                //in case endKeep is nullptr 
                tail = frontKeep;
            }
        }
    }
}

ostream &operator<<(ostream &os, const Sequence &s)
{

    //this REALLY confused me for the longest time but you can still access the sequence node even though it's private  
    Sequence::SequenceNode *currentNode = s.head;
    os << "<";

    while (currentNode != nullptr)
    {
        //if its the last element in the sequence, format differently
        if (currentNode->next == nullptr)
        {
            os << currentNode->elt;
        }
        else
        {
            os << currentNode->elt << ", ";
        }
        currentNode = currentNode->next;
    }

    os << ">" << endl;

    return os;
}