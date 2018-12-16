#include "HashMap.hpp"

namespace
{
    unsigned int hash(const std::string&s)
    {
        unsigned int g = 31;
        unsigned int h = 0;
        
        for (unsigned int i = 0; i < s.length(); i++)
        {
            h = g * h + s[i];
        }
        
        return h;
    }
}

HashMap::HashMap()
:buckets{ initialBucketCount }, numValues{ 0 }    //initializing members
{
    hasher = hash;
    newHash = new Node*[buckets];    //create a new hash
    initializeArray(newHash, buckets);    //initialize array with null
    
}



HashMap::HashMap(HashFunction hasher)    //takes in the hasher and sets in to our function
:buckets{initialBucketCount},numValues{0} //mem intiializers
{
    this->hasher = hasher;    //hasher= our hash function
    newHash = new Node*[buckets];
    initializeArray(newHash, buckets);
    
}

HashMap::HashMap(const HashMap& hm)
:buckets{ hm.buckets },numValues{hm.numValues}
{
    hasher=hm.hasher;
    newHash = new Node*[hm.buckets];
    initializeArray(newHash, buckets);
    arrayCopy(newHash, hm.newHash, buckets);
    
}



HashMap& HashMap::operator=(const HashMap& hm)
{
    if (this != &hm)
    {
        this->~HashMap();
        newHash = new Node*[hm.buckets];
        initializeArray(newHash, hm.buckets);
        arrayCopy(newHash, hm.newHash, hm.buckets);
        hasher = hm.hasher;
        numValues = hm.numValues;
        buckets = hm.buckets;
        
    }
    return *this;
}


void HashMap::add(const std::string& key, const std::string& value)
{
    if(!contains(key))
    {
        int index = hasher(key) % buckets;
        numValues++;
        Node *nn = new Node;
        nn->key = key;
        nn->value = value;
        nn->next = newHash[index];
        newHash[index] = nn;
        
        
        if (loadFactor()>0.8)
        {
            int newCap = buckets * 2 + 1;
            
            Node** newHashMap = new Node*[newCap];    //create a new node called n2
            
            initializeArray(newHashMap, newCap);
            
            for (int i = 0; i < buckets; i++)
            {
                Node* temp = newHash[i];
                while (temp != nullptr)
                {
                    /*  index = hash(temp->key) % newCap;
                     
                     Node *n2 = new Node;
                     n2->key = key;
                     n2->value = value;
                     n2->next = newHashMap[index];
                     newHashMap[index] = n2;
                     temp = temp->next;
                     */
                    Node *n2=temp;
                    temp=temp->next;
                    Node*& b=newHashMap[hasher(n2->key)%newCap];
                    n2->next=b;
                    b=n2;
                }
            }
            
            /* this->~HashMap();
             buckets = newCap;
             newHash = newHashMap;
             */
            delete[]newHash;
            //   *this->~HashMap();
            newHash=newHashMap;
            buckets=newCap;
        }
    }
    else
    {
    }
    
    
    
}

void HashMap::remove(const std::string &key)
{
    if (contains(key))
    {
        int index = hasher(key) % buckets;    //hash key and mod size
        Node* temp;    //created a temp to point to list
        Node* temp2;    //temp 2
        
        if (newHash[index]->key == key) // if the keys are the same
        {
            temp = newHash[index]->next; //point tempararly to the next key
            delete newHash[index];    //delete the passed key
            newHash[index] = temp;        //point back to temp aka next key
        }
        else
        {
            temp = newHash[index];    //point temp to the beg of list
            temp2 = temp;
            //check until temp is finished or the keys match
            while (temp != nullptr && temp->key != key)
            {
                temp2 = temp;    //set temp2 to 1
                temp = temp->next;    //point to the next
            }
            temp2->next = temp->next;    //connect the list together
            delete temp;    //remove the needed key
        }
        numValues--;    //remove from value count
        deleted[d1]=key;
        d1++;
    }
    
}

HashMap::~HashMap()
{
    for (int i = 0; i < buckets; i++)
    {
        Node* deletePtr = newHash[i];
        
        while (deletePtr != nullptr)
        {
            newHash[i] = newHash[i]->next;
            delete deletePtr;
            deletePtr = newHash[i];
        }
        
    }
    delete[] newHash;
    
    
}


void HashMap::arrayCopy(Node** target, Node** const &source,  int size)
{
    
    
    for (int i = 0; i < size; i++)
    {
        Node* current = source[i];
        if (current != nullptr)
        {
            target[i] = new Node;
            Node*temp = target[i];
            
            while (current != nullptr)
            {
                temp->key = current->key;
                temp->value = current->value;
                //temp->next = new Node;
                
                if (current->next != nullptr)
                {
                    temp->next=new Node;
                    temp = temp->next;
                }
                else
                    temp->next = nullptr;
                
                current = current->next;
            }
        }
        
        
    }
    
    
}


bool HashMap::contains(const std::string& key) const
{
    int index = hasher(key) % buckets;    //hash function
    //make temp pointer and point to hashlist at index to then check the linkedlist
    Node* temp = newHash[index];
    // bool t2 = false;
    if (temp != nullptr)
    {
        while (temp->next != nullptr&&temp->key != key)
        {
            //std::cout<<temp->key<<std::endl;
            temp = temp->next;
        }
        if (temp->key == key)
        {
            return true;
        }
        
        else
            return false;
        
    }
    
    else
        return false;
}



void HashMap::initializeArray(Node** &n, int size)
{
    for (int i = 0; i < size; i++)
    {
        n[i] = nullptr;
    }
    
}

std::string HashMap::value(const std::string& key)const
{
    if (contains(key))    //see if the key is in the list
    {
        int index = hasher(key) % buckets;    //hash to the key index
        Node* temp = newHash[index];    //create a node pointing to index
        while (temp->key != key)    //loop trough linkedlist
        {
            temp = temp->next;
        }
        //once while stops you will be at the correct value
        return temp->value;
    }
    //if not in the list return empty string
    else
        return "";
    
}

unsigned int HashMap::size() const
{
    return numValues;
}

unsigned int HashMap:: bucketCount()const
{
    return buckets;
}

unsigned int HashMap::maxBucketSize()const
{
    int m1 = 0;
    int m2;
    //loop list
    for (int i = 0; i<buckets; i++)
    {
        m2 = 0;
        //create a temp node pointing at the current index
        Node* temp = newHash[i];
        //if index inst null count how big it is
        while (temp != nullptr)
        {
            
            m2++;    //incriment count
            temp = temp->next;        //point to the next
        }
        if (m2 > m1)    //check which one is biggest
            m1 = m2;
    }
    
    return m1;
}

double HashMap::loadFactor()const
{
    //double r;
    return (double)size()/buckets;
    // return r;
}

bool HashMap::getDeleted(const std::string &key)
{
    bool b1=false;
    int s=20;
    
    for (int i = 0; i < s; i++)
    {
        if(deleted[i]==key)
        {
            b1=true;
            return b1;
        }
    }
    return b1;
}

void HashMap::clear()
{
    //loop trough the map
    for(int i=0;i<numValues;i++)
    {
        //temp pointer to the list
        Node* temp=newHash[i];
        //while we havent reached the end loop the list
        while (temp!=nullptr) {
            //point to the next item
            newHash[i]=newHash[i]->next;
            //delete the current
            delete temp;
            //point to the new item
            temp=newHash[i];
        }
        //set the old item to null
        newHash[i]=nullptr;
    }
    //buckets=0; //set the array to 0
    numValues=0;
    
}



