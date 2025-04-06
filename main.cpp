#include<iostream>
#include<cmath>

const double EPSILON_0 = 8.854e-12;
const double MU_0 = 4 * M_PI * 1e-7;

class Field{
	protected: 
		double *value;

	public: 
		Field(){
			value = new double[3]{0.0, 0.0, 0.0};
   		 }
	
		Field(double x, double y, double z){
			value = new double[3]{x, y, z};
   		 }

		Field(const Field& other){
			value = new double[3];
       			 for (int i = 0; i < 3; ++i) {
            			value[i] = other.value[i];
       			 }
    		}

		virtual ~Field() {
     		delete[] value;
    		}

		virtual void printMagnitude() const{
			std::cout << "components: ("
					<< value[0] << ", "
                 			 << value[1] << ", "
                 			 << value[2] << ")\n";
			}

		virtual void calculateField(double, double) = 0;
		};


class Electric_Field : public Field{
	private: 
		double calculated_E;
	public:
	Electric_Field() : Field(), calculated_E(0.0) {}
	Electric_Field(double x, double y, double z) : Field(x, y, z), calculated_E(0.0) {}

	Electric_Field(const Electric_Field& other) : Field(other), calculated_E(other.calculated_E) {}

	void calculateField(double Q, double r) override {
        calculated_E = Q / (4 * M_PI * r * r * EPSILON_0);
   	 }


	double getCalculatedE() const {
        return calculated_E;
    	}

	Electric_Field operator+(const Electric_Field& other) {
        return Electric_Field(
            value[0] + other.value[0],
            value[1] + other.value[1],
            value[2] + other.value[2]
        );
    }

	
	friend std::ostream& operator<<(std::ostream& os, const Electric_Field& e) {
        os << "Electric Field Components: ("
           << e.value[0] << ", "
           << e.value[1] << ", "
           << e.value[2] << ")";
        return os;
    }
};

class Magnetic_Field : public Field {
	private:
   		double calculated_B;

	public:
		Magnetic_Field() : Field(), calculated_B(0.0) {}
		Magnetic_Field(double x, double y, double z) : Field(x, y, z), calculated_B(0.0) {}

		Magnetic_Field(const Magnetic_Field& other) : Field(other), calculated_B(other.calculated_B) {}
		
		void calculateField(double I, double r) override {
     			calculated_B = I / (2 * M_PI * r * MU_0);
   		 }

		double getCalculatedB() const {
     	   		return calculated_B;
   		 }

	Magnetic_Field operator+(const Magnetic_Field& other) {
        return Magnetic_Field(
            value[0] + other.value[0],
            value[1] + other.value[1],
            value[2] + other.value[2]
        );
    }

		friend std::ostream& operator<<(std::ostream& os, const Magnetic_Field& b) {
        os << "Magnetic Field Components: ("
           << b.value[0] << ", "
           << b.value[1] << ", "
           << b.value[2] << ")";
        return os;
    }
};


int main(){
	Electric_Field e1(0, 1e5, 1e3);
    	Magnetic_Field b1(1e-3, 0, 2e-3);

    	std::cout << "Initial Field Values:\n";
    	e1.printMagnitude();
    	b1.printMagnitude();

	double charge = 1e-6;
	double distance = 0.1;
	e1.calculateField(charge, distance);
   	std::cout << "\nElectric Field calculated using Gauss' Law: "
       		<< e1.getCalculatedE() << " N/C\n";

	double current = 10; // Amps
   	b1.calculateField(current, distance);
    	std::cout << "Magnetic Field calculated using Ampere's Law: "
              << b1.getCalculatedB() << " T\n";

	Electric_Field e2(1e2, 2e2, 3e2);
    Electric_Field e3 = e1 + e2;

    Magnetic_Field b2(2e-3, 1e-3, 3e-3);
    Magnetic_Field b3 = b1 + b2;

    std::cout << "\nCombined Electric Field e3 = e1 + e2:\n" << e3 << std::endl;
    std::cout << "Combined Magnetic Field b3 = b1 + b2:\n" << b3 << std::endl;

    return 0;
}
