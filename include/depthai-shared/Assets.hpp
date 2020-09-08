#pragma once

// standard
#include <cstdint>
#include <unordered_map>
#include <exception>

// libraries
#include <nlohmann/json.hpp>


namespace dai
{

// This class represent a single asset
class Asset {
    std::uint8_t* data;
    std::uint32_t size;
    std::uint32_t alignment = 1;
public:
    Asset(std::uint8_t* d, std::uint32_t s, std::uint32_t a = 1) : data(d), size(s), alignment(a){}
    std::uint8_t* getData() const {return data;}
    std::uint32_t getSize() const {return size;}
    std::uint32_t getAlignment() const {return alignment;}

};


// This is a serializable class, which acts as readonly access to assets
class Assets {
    
protected: 
    std::uint8_t* pStorageStart = nullptr;

    struct AssetInternal{
        std::uint32_t offset, size, alignment;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(AssetInternal, offset, size, alignment);
    };

    // maps string to Asset
    std::unordered_map<std::string, AssetInternal> map;

public:
    void setStorage(std::uint8_t* ps){
        pStorageStart = ps;
    }

    bool has(std::string key){
        return (map.count(key) > 0);
    }

    Asset get(std::string key){
        AssetInternal internal = map.at(key);
        return Asset(pStorageStart + internal.offset, internal.size, internal.alignment);
    }

    std::vector< std::pair<std::string, Asset>> getAll(){
        std::vector< std::pair<std::string, Asset>> allAssets;
        for(const auto& kv : map){
            allAssets.push_back( {kv.first, get(kv.first)} );
        }
        return allAssets;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Assets, map);

};

// Subclass which has its own storage
class AssetManager : public Assets {
    std::vector<std::uint8_t> storage;
public: 

    // copy the contents pointed to by Asset 'a' to storage, with alignment a.alignment
    void add(std::string key, Asset a){
        // make sure that key doesn't exist already
        if(map.count(key) > 0) throw std::logic_error("An Asset with the key: " + key + " already exists.");
        
        // calculate additional bytes needed to offset to alignment
        int toAdd = 0;
        if(a.getAlignment() > 1 && storage.size() % a.getAlignment() != 0){
            toAdd = a.getAlignment() - (storage.size() % a.getAlignment()); 
        }

        // calculate offset
        std::uint32_t offset = storage.size() + toAdd;

        // Add alignment bytes
        storage.resize(storage.size() + toAdd);

        // copy data
        storage.insert(storage.end(), a.getData(), a.getData() + a.getSize());

        // Add to map the currently added asset
        AssetInternal internal;
        internal.offset = offset;
        internal.size = a.getSize();
        internal.alignment = a.getAlignment();
        map[key] = internal;

    }

    std::vector<std::uint8_t> serialize(){
        return storage;
    }
};







} // namespace dai
