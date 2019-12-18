#include <map>

extern void initialiseCoordinator(ConfigurableSettings& settings);
extern void loopCoordinator(ConfigurableSettings& settings);
extern std::map<int, void (*)(ConfigurableSettings& settings)> shows;
