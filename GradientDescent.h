#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H

#include <functional>
#include <vector>
#include <cmath>
#include <numeric>
#include <iostream>

double vector_norm(const std::vector<double>& v){
    return std::sqrt(std::inner_product(v.cbegin(),v.cend(),v.cbegin(),0.0));
}

std::vector<double> gradient_method(const std::function<double(std::vector<double>)>& f,
                       const std::function<std::vector<double>(std::vector<double>)>& grad,
                       std::vector<double> x0,
                       const double tolr, const double tols,
                       double alpha, const unsigned int maxIter, const double sigma){

    std::vector<double> xk(x0);
    std::vector<double> x_step(x0);
    std::vector<double> grad_x0;
    bool check_step = true,check_res = true;
    unsigned int iter {0};

    while(check_step && check_res && iter<maxIter){
        ++iter;

        grad_x0 = grad(x0);
        // Armijo Rule
        do{
            alpha /= 2;
            for (size_t i = 0; i != x0.size(); ++i){
                xk[i] = x0[i] - alpha*grad_x0[i];
                x_step[i] = xk[i] - x0[i];
            }
        } while ( std::abs(f(x0)-f(xk)) <= sigma* alpha* vector_norm(grad_x0)* vector_norm(grad_x0) );

        check_step = vector_norm(x_step) > tols;
        check_res = std::abs(f(xk)-f(x0)) > tolr;
        x0 = xk;
    }
    std::cout << "\nGradient Descent with Armijo Rule Completed in " << iter << " Iterations" << std::endl;

    std::cout << "Exit Condition(s):" ;
    if (!check_step) std::cout << " Step Length";
    if (!check_res) std::cout << " Residual";
    if (iter == maxIter) std::cout << " Maximum Iterations";

    return xk;
}

#endif //GRADIENTDESCENT_H
