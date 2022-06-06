main : GPIO_PWM_API.o main.o
	g++ -o main GPIO_PWM_API.o main.o -lwiringPi
GPIO_PWM_API.o : GPIO_PWM_API.cpp
	g++ -c -o GPIO_PWM_API.o GPIO_PWM_API.cpp -lwiringPi
main.o : main.cpp
	g++ -c -o main.o main.cpp -lwiringPi
clean:
	rm *.o main
