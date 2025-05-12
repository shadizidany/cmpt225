// Assignment 2A
// QuadraticProbing.h: Generic hash table implementation using quadratic probing for collision handling
#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional> // For std::hash
#include <string>
using namespace std;

// Forward declaration of helper function that
// finds the next prime number greater than or equal to n
int nextPrime( int n );

// QuadraticProbing Hash table class
// Implements a hash table using quadratic probing for collision resolution
// The table automatically resizes when the load factor exceeds 0.5
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x ) --> Insert x
// bool remove( x ) --> Remove x
// bool contains( x ) --> Return true if x is present
// void makeEmpty( ) --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable
{
public:
    // Constructor: Creates a hash table with given size (or 101 by default)
    // Size is adjusted to the next prime number
    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
    { makeEmpty( ); }

    // Returns true if x is found in the hash table
    bool contains( const HashedObj & x ) const
    {
        return isActive( findPos( x ) );
    }

    // Removes all elements from the hash table
    // Sets all slots to EMPTY and resets currentSize to 0
    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
            entry.info = EMPTY;
    }

    // Inserts x into the hash table using lvalue reference
    // Returns false if x already exists, true if insertion successful
    // Automatically triggers rehash if load factor exceeds 0.5
    bool insert( const HashedObj & x )
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;
        if( array[ currentPos ].info != DELETED )
            ++currentSize;
        array[ currentPos ].element = x;
        array[ currentPos ].info = ACTIVE;
        // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );
        return true;
    }

    // Inserts x into the hash table using rvalue reference (move semantics)
    // Returns false if x already exists, true if insertion successful
    // Automatically triggers rehash if load factor exceeds 0.5
    bool insert( HashedObj && x )
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;
        if( array[ currentPos ].info != DELETED )
            ++currentSize;
        array[ currentPos ] = std::move( x );
        array[ currentPos ].info = ACTIVE;
        // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );
        return true;
    }

    // Removes x from the hash table
    // Returns true if x was found and removed, false if x wasn't found
    // Marks the slot as DELETED rather than EMPTY
    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;
        array[ currentPos ].info = DELETED;
        return true;
    }

    // Enum to track the state of each slot in the hash table
    // ACTIVE: Contains a valid element
    // EMPTY: Never been used
    // DELETED: Previously contained an element, now removed
    enum EntryType { ACTIVE, EMPTY, DELETED };

private:
    // Internal structure representing each slot in the hash table
    struct HashEntry
    {
        HashedObj element;  // The stored element
        EntryType info;     // Status of this slot (ACTIVE/EMPTY/DELETED)
        
        // Constructor for lvalue references
        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
            : element{ e }, info{ i } { }
        
        // Constructor for rvalue references (move semantics)
        HashEntry( HashedObj && e, EntryType i = EMPTY )
            : element{ std::move( e ) }, info{ i } { }
    };

    vector<HashEntry> array;    // The actual hash table array
    int currentSize;           // Number of ACTIVE + DELETED elements in the table

    // Returns true if the position contains an active element
    bool isActive( int currentPos ) const
    { return array[ currentPos ].info == ACTIVE; }

    // Finds the position where x should be in the table
    // Uses quadratic probing to resolve collisions
    // Probing sequence: h(x), h(x) + 1, h(x) + 3, h(x) + 5, ...
    int findPos( const HashedObj & x ) const
    {
        int offset = 1;
        int currentPos = myhash( x );
        while( array[ currentPos ].info != EMPTY &&
               array[ currentPos ].element != x )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }
        return currentPos;
    }

    // Rehashes the table when load factor exceeds 0.5
    // Creates a new table of double size and transfers all active elements
    void rehash( )
    {
        vector<HashEntry> oldArray = array;
        // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( auto & entry : array )
            entry.info = EMPTY;
        // Copy table over
        currentSize = 0;
        for( auto & entry : oldArray )
            if( entry.info == ACTIVE )
                insert( std::move( entry.element ) );
    }

    // Computes the hash value for an element
    // Uses the standard hash function for the type and mods by table size
    size_t myhash( const HashedObj & x ) const
    {
        // static hash function object (hf) is created once and reused across all calls to myhash()
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }
};
#endif