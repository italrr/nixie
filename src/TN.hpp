#ifndef TN_GRAPHICS_HPP
    #define TN_GRAPHICS_HPP
    
    #include "Types.hpp"

    namespace nx {

		struct Bitmap {
			nx::Pixel *pixels;
			v2<int> size;
			Bitmap();
			Bitmap(unsigned w, unsigned h, const nx::Color &fill);
			~Bitmap();
			nx::Pixel sample(int x, int y);
			void clear();
			bool load(const std::string &path);
			void create(unsigned w, unsigned h, const nx::Color &fill);
		};

		namespace Draw {
			bool Bitmap(nx::Bitmap *bm, const nx::v2<int> &pos, const nx::v2<int> &size, const nx::v2<float> &origin, float angle);
			bool Pixel(int x, int y, const nx::Pixel &p);
			bool Line(int x1, int y1, int x2, int y2, const nx::Pixel &p);
		}

		v2<int> gfxSize();
		v2<int> gfxRSize();
		v2<int> gfxScale();

		float gfxDelta();
        bool gfxInit(int w, int h, int scalex, int scaley);
        void gfxDraw();
        void gfxEnd();
        void exit();
        bool isRunning();


        bool kbCheck(unsigned k);
        bool kbPress(unsigned k);
        bool kbPressOnce(unsigned k);
        bool kbPressed(unsigned k);
        bool kbReleased(unsigned k);

        static const unsigned keyA 				= 0;
		static const unsigned keyB 				= 1;
		static const unsigned keyC 				= 2;
		static const unsigned keyD 				= 3;
		static const unsigned keyE 				= 4;
		static const unsigned keyF 				= 5;
		static const unsigned keyG 				= 6;
		static const unsigned keyH 				= 7;
		static const unsigned keyI 				= 8;
		static const unsigned keyJ 				= 9;
		static const unsigned keyK 				= 10;
		static const unsigned keyL 				= 11;
		static const unsigned keyM 				= 12;
		static const unsigned keyN 				= 13;
		static const unsigned keyO 				= 14;
		static const unsigned keyP 				= 15;
		static const unsigned keyQ 				= 16;
		static const unsigned keyR 				= 17;
		static const unsigned keyS 				= 18;
		static const unsigned keyT 				= 19;
		static const unsigned keyU 				= 20;
		static const unsigned keyV 				= 21;
		static const unsigned keyW 				= 22;
		static const unsigned keyX 				= 23;
		static const unsigned keyY 				= 24;
		static const unsigned keyZ 				= 25;
		static const unsigned key0 				= 26;
		static const unsigned key1 				= 27;
		static const unsigned key2 				= 28;
		static const unsigned key3 				= 29;
		static const unsigned key4 				= 30;
		static const unsigned key5 				= 31;
		static const unsigned key6 				= 32;
		static const unsigned key7 				= 33;
		static const unsigned key8 				= 34;
		static const unsigned key9 				= 35;
		static const unsigned keyESCAPE 			= 36;
		static const unsigned keyLCONTROL 			= 37;
		static const unsigned keyLSHIFT 			= 38;
		static const unsigned keyLALT 				= 39;
		static const unsigned keyLSYSTEM 			= 40;
		static const unsigned keyRCONTROL 			= 41;
		static const unsigned keyRSHIFT 			= 42;
		static const unsigned keyRALT 				= 43;
		static const unsigned keyRSYSTEM 			= 44;
		static const unsigned keyMENU 				= 45;
		static const unsigned keyLBRACKET 			= 46;
		static const unsigned keyRBRACKET 			= 47;
		static const unsigned keySEMICOLON 		= 48;
		static const unsigned keyCOMMA 			= 49;
		static const unsigned keyPERIOD 			= 50;
		static const unsigned keyQUOTE 			= 51;
		static const unsigned keySLASH 			= 52;
		static const unsigned keyBACKSLASH 		= 53;
		static const unsigned keyTILDE 			= 54; // ~
		static const unsigned keyEQUAL 			= 55;
		static const unsigned keyDASH 				= 56;
		static const unsigned keySPACE 			= 57;
		static const unsigned keyENTER 			= 58;
		static const unsigned keyBACK 				= 59;
		static const unsigned keyTAB 				= 60;
		static const unsigned keyPAGEUP 			= 61;
		static const unsigned keyPAGEDOWN 			= 62;
		static const unsigned keyEND 				= 63;
		static const unsigned keyHOME 				= 64;
		static const unsigned keyINSERT 			= 65;
		static const unsigned keyDELETE 			= 66;
		static const unsigned keyADD 				= 67;
		static const unsigned keySUBTRACT 			= 68;
		static const unsigned keyMULTIPLY 			= 69;
		static const unsigned keyDIVIDE 			= 70;
		static const unsigned keyLEFT 				= 71;
		static const unsigned keyRIGHT 			= 72;
		static const unsigned keyUP 				= 73;
		static const unsigned keyDOWN 				= 74;
		static const unsigned keyNUMPAD0 			= 75;
		static const unsigned keyNUMPAD1 			= 76;
		static const unsigned keyNUMPAD2 			= 77;
		static const unsigned keyNUMPAD3 			= 78;
		static const unsigned keyNUMPAD4 			= 79;
		static const unsigned keyNUMPAD5 			= 80;
		static const unsigned keyNUMPAD6 			= 81;
		static const unsigned keyNUMPAD7 			= 82;
		static const unsigned keyNUMPAD8 			= 83;
		static const unsigned keyNUMPAD9 			= 84;
		static const unsigned keyF1 				= 85;
		static const unsigned keyF2 				= 86;
		static const unsigned keyF3 				= 87;
		static const unsigned keyF4 				= 88;
		static const unsigned keyF5 				= 89;
		static const unsigned keyF6 				= 90;
		static const unsigned keyF7 				= 91;
		static const unsigned keyF8 				= 92;
		static const unsigned keyF9 				= 93;
		static const unsigned keyF10 				= 94;
		static const unsigned keyF11 				= 95;
		static const unsigned keyF12 				= 96;
		static const unsigned keyF13 				= 97;
		static const unsigned keyF14 				= 98;
		static const unsigned keyF15 				= 99;
		static const unsigned keyPAUSE				= 100;

    }

#endif