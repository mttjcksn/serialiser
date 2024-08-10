#pragma once

#include <vector>
#include <map>
#include <unordered_map>

///  Serialiser class 
/**
 * Serialise and deserialise built-in types, STL containers, and custom types with supporting methods.
 * A supported type must have a default constructor and implement the serialise and deserialise function templates below.
 * TODO: Remove requirement for default constructor.
*/
class Serialiser {
public:

    /// Serialise map
    /**      
      @param objectMap Reference to std::map of objects to serialise
      @return Serialised data as std::vector of chars
    */
    template <class K, class T>
    static std::vector<char> serialise(const std::map<K,T> &objectMap)
    {
        std::vector<char> out;
        appendVector(out, serialise(static_cast<int32_t>(objectMap.size())));
        for(auto& item:objectMap)
        {
            appendVector(out, serialise(item.first));
            appendVector(out, serialise(item.second));
        }
        return out;
    }

    /// Deserialise map
    /**
      @param buffer Pointer to data to deserialise
      @param outMap Reference to std::map to fill with deserialised data
      @return Number of bytes read in deserialisation
    */
    template <class K, class T>
    static size_t deserialise(const char* buffer, std::map<K,T> &outMap)
    {
        outMap.clear();
        char* readHead = (char*)buffer;
        int32_t nObjects = 0;
        readHead += deserialise(readHead, nObjects);
        K key;
        for(int i=0;i<nObjects;i++)
        {
            readHead += deserialise(readHead, key);
            T obj;
            readHead += deserialise(readHead, obj);
            outMap[key]=obj;
        }
        return readHead-buffer;
    }

    /// Serialise unordered map
    /**      
      @param objectMap Reference to std::unordered_map of objects to serialise
      @return Serialised data as std::vector of chars
    */
    template <class K, class V>
    static std::vector<char> serialise(const std::unordered_map<K,V> &objectMap)
    {
        std::vector<char> out;
        appendVector(out, serialise(static_cast<int32_t>(objectMap.size())));
        for(auto& item:objectMap)
        {
            appendVector(out, serialise(item.first));
            appendVector(out, serialise(item.second));
        }
        return out;
    }

    /// Deserialise unordered map
    /**
      @param buffer Pointer to data to deserialise
      @param outMap Reference to std::unordered_map to fill with deserialised data
      @return Number of bytes read in deserialisation
    */
    template <class K, class V>
    static size_t deserialise(const char* buffer, std::unordered_map<K,V> &outMap)
    {
        outMap.clear();
        char* readHead = (char*)buffer;
        int32_t nObjects = 0;
        readHead += deserialise(readHead, nObjects);
        K key;
        for(int i=0;i<nObjects;i++)
        {
            readHead += deserialise(readHead, key);
            V obj;
            readHead += deserialise(readHead, obj);
            outMap[key]=obj;
        }
        return readHead-buffer;
    }

    /// Serialise vector
    /**      
      @param objectVector Reference to std::vector of objects to serialise
      @return Serialised data as std::vector of chars
    */
    template <class T>
    static std::vector<char> serialise(const std::vector<T>& objectVector)
    {
        std::vector<char> out;
        appendVector(out, serialise(static_cast<int32_t>(objectVector.size())));
        for(auto& item:objectVector)
        {
            appendVector(out, serialise(item));
        }
        return out;
    }

    /// Deserialise vector
    /**
      @param buffer Pointer to data to deserialise
      @param outMap Reference to std::map to fill with deserialised data
      @return Number of bytes read in deserialisation
    */
    template <class T>
    static size_t deserialise(const char* buffer, std::vector<T> &outVector)
    {
        outVector.clear();
        char* readHead = (char*)buffer;
        int32_t nObjects = 0;
        readHead += deserialise(readHead, nObjects);
        for(int i=0;i<nObjects;i++)
        {
            T obj;
            readHead += deserialise(readHead, obj);
            outVector.push_back(obj);
        }
        return readHead-buffer;
    }

    /// Append vector helper, just to keep code neat
    /**
      @param buffer Reference to vector to append to
      @param item Vector to append to buffer
    */
    static inline void appendVector(std::vector<char> &buffer, std::vector<char> item)
    {
        buffer.insert(buffer.end(), item.data(), item.data() + item.size());
    }

    template <typename T>
    static std::vector<char> serialise(const T& obj)
    {        
        if constexpr(std::is_base_of<Serialiser, T>::value)
        {
            return T::serialise(obj); // Call custom serialisation
        } 
        else
        {
            // Call default serialisation
            const char* data = reinterpret_cast<const char*>(&obj);
            std::vector<char> ret(data, data + sizeof(obj));
            return ret;
        }
        
    }

    template <typename T>
    static size_t deserialise(const char* serialisedData, T& objOut)
    {
        if (!serialisedData)
        {
            return 0;
        }

        if constexpr(std::is_base_of<Serialiser, T>::value)
        {
            return T::deserialise(serialisedData, objOut); // Call custom serialisation
        } 
        else
        {
            size_t dataSize = sizeof(T);
            std::memcpy(&objOut, serialisedData, dataSize);
            return dataSize;
        }
    }

};