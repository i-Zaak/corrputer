#include "../ConfigFile.h"

#include <iostream>
#include "../common.h"

int configFileTest()
{
  ConfigFile cf("test_config.txt");

  std::string foo;
  std::string water;
  std::string four;
  std::string unknown;

  std::vector<std::string> sections = cf.GetSections();

  for (std::vector<std::string>::iterator i = sections.begin(); i < sections.end(); i++) {
    std::cout<<"Section: " << *i << std::endl;
  }

  foo      = cf.Value("section_1","foo"     , "?");
  water    = cf.Value("section_2","water"   , "?");
  four     = cf.Value("section_2","four"    , "?");
  unknown  = cf.Value("section_3","unknown" , "?");

  std::cout << foo     << std::endl;
  std::cout << water   << std::endl;
  std::cout << four    << std::endl;
  std::cout << unknown << std::endl;

  return 0;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% ConfigFileTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% configFileTest (ConfigFileTest)" << std::endl;
    configFileTest();
    std::cout << "%TEST_FINISHED% time=0 configFileTest (ConfigFileTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

