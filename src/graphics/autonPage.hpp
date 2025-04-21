//Includes
#include "main.h" // IWYU pragma: keep

//Class AutonPage with constructor
class AutonPage {
    public:
        //Static variables
        static lv_obj_t* tabView;
        static std::vector<void (*)()> callbacks;

        //Member variables
        lv_obj_t* page;
        void (*callback)();

        //Static methods
        static void initialize();

        //Constructor
        AutonPage(const char* title, const char* description, void (*callback)());
};