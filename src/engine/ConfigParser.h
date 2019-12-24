#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>
#include <glm/glm.hpp>
#include <fstream>
#include <unordered_map>
#include <functional>

struct ParserTypeInfo {
    int typeId;
    void* field;
    
    ParserTypeInfo() {}
    ParserTypeInfo(int typeId, void* field) :
        typeId(typeId), field(field) {
    }
};

class ConfigParser {
    static std::unordered_map<int, std::function<void(std::ifstream&, void*)>> typeParsers;

    std::unordered_map<std::string, ParserTypeInfo> infos;
    std::unordered_map<std::string, std::function<void(std::ifstream&)>> customParsers;

public:
    bool load(const std::string& path);

protected:
    template<typename T>
    void parse(const std::string& name, T* field) {
        infos[name] = ParserTypeInfo(getTypeId<T>(), field);
    }

    void customParse(const std::string& name, std::function<void(std::ifstream&)> customParser) {
        customParsers[name] = customParser;
    }

private:
    template<typename T>
    static void parseField(std::ifstream& file, void* field) {
        file >> *static_cast<T*>(field);
    }

    static void parseVec2(std::ifstream& file, void* field);
    static void parseVec3(std::ifstream& file, void* field);

    static int lastTypeId;
    template<typename T>
    static int getTypeId(){
        static int id = ++lastTypeId;
        return id;
    }
};

#endif