#ifndef TN_TOOLS_HPP
    #define TN_TOOLS_HPP
    
    #include "Types.hpp"

    namespace nx {

        namespace File {
            bool exists(const std::string &path);
        }

        namespace Math {
            static const float PI = 3.14159265358979323846;

            inline float rads(float deg){
                return deg * 0.01745329251994329576923690768489;
            }
            inline float degs(float rads){
                return rads * (180.0f/PI);	
            }            
        }

    };


#endif