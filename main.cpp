#include "GradientDescent.h"

double fun(const std::vector<double> &x){
    return x[0]*x[1] + 4*std::pow(x[0],4) + x[1]*x[1] + 3*x[0];
}

std::vector<double> grad(const std::vector<double> &x){
    return std::vector<double> {x[1] + 16*std::pow(x[0],3) + 3, x[0] + 2*x[1]};
}

int main() {

    std::vector<double> x_0{0,0}; //starting point
    double tolr = 1e-6; //residual tolerance
    double tols = 1e-6; //step size tolerance
    double alpha_0 = 0.1; //initial learning rate
    unsigned int maxIter = 100; //maximum number of iterations
    double sigma = 0.5; //values in (0,0.5), Armijo rule parameter

    std::vector<double> x_opt = gradient_method(fun,grad,x_0,tolr,tols,alpha_0,maxIter,sigma);

    //Display Result
    std::cout << "\n\nMinimizer is x = {";
    for (size_t i=0; i!= x_opt.size()-1; ++i){
        std::cout << x_opt[i] << ",";
    }
    std::cout << x_opt[x_opt.size()-1] << "}" << std::endl;
    std::cout << "f(x) = " << fun(x_opt) << std::endl;

}
