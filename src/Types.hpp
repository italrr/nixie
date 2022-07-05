#ifndef TN_TYPES_HPP
    #define TN_TYPES_HPP

    #include <string>
    #include <vector>
    #include <unordered_map>
    #include <stdint.h>

    namespace nx {

        template<typename T>
        struct v2 {
            T x;
            T y;

            v2(){
                this->x = 0;
                this->y = 0;
            }

            v2(T x, T y){
                set(x, y);
            }

            v2(T c){
                set(c, c);
            }

            void set(T x, T y){
                this->x = x;
                this->y = y;
            }

            void set (T c){
                set(c, c);
            }
        };

		struct Color {
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;	

            Color(unsigned char c){
                set(c);
            }
            
            Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255){
                set(r, g, b, a);
            }  

            void set(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255){
                this->r = r;
                this->g = g;
                this->b = b;
                this->a = a;
            }       

            void set(unsigned char c){
                this->r = c;
                this->g = c;
                this->b = c;
            }          
		};       

		struct Pixel {
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
            Pixel(){
                r = g = a = 255;
            }
            Pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255){
                this->r = r;
                this->g = g;
                this->b = b;
                this->a = a;
            }
            Pixel(const nx::Color &color){
                this->r = color.r;
                this->g = color.g;
                this->b = color.b;
                this->a = color.a;
            }
		}; 

    }

#endif