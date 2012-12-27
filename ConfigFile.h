/*
 * Taken from: https://github.com/ReneNyffenegger/development_misc/tree/master/c++/helpers
 */
#ifndef CONFIG_FILE_H__
#define CONFIG_FILE_H__

#include <string>
#include <map>
#include <vector>

class ConfigFile {
    std::map   <std::string, std::string> content_;
    std::vector<std::string>              sections_;
public:
    ConfigFile(std::string const& configFile);

    std::vector<std::string> GetSections();

    std::string const& Value(std::string const& section, std::string const& entry) const;
    std::string const& Value(std::string const& section, std::string const& entry, std::string const& value);
};

#endif

