a.out: main.o custom_filter.o 
	g++ -O3 -mfpu=neon main.o custom_filter.o

custom_filter.o: custom_filter.s
	as -mfpu=neon -o custom_filter.o custom_filter.s -g

main.o: main.cc
	#g++ -c -Dcimg_display=0 -fexceptions main.cc
	#g++ -O1 -c -Dcimg_display=0 -fexceptions main.cc
	#g++ -O3 -c -Dcimg_display=0 -fexceptions main.cc
#	g++ -O3 -mfpu=neon -c -Dcimg_display=0 -Dstudent_darken -fexceptions main.cc 
	g++ -O3 -mfpu=neon -c -Dcimg_display=0 -Dcustom -fexceptions main.cc 

clean:
	rm -rf *.o a.out output.*
