add_library(lib Controller/Controller.h Controller/Controller.cpp Model/Model.h Model/Model.cpp View/View.h View/View.cpp)
target_link_libraries(lib PRIVATE cpr::cpr)
target_link_libraries(lib PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(lib PRIVATE ftxui::screen PRIVATE ftxui::dom PRIVATE ftxui::component)