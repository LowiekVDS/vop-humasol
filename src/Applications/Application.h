#include "../Layers/ApplicationLayer.h"

class Application : public ApplicationLayer {

    public:
        Application() : ApplicationLayer() {}
        ~Application() {}
    
        /**
         * @brief Runs the application
         * 
         * @return true when the application is still running
         * @return false when the application is finished
         */
        virtual bool run();
};