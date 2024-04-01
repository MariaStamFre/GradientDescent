#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H
//@note nomally cpp header files have extension hpp or H, but it is not a strict rule, you can use h as well.
// but then it is more difficult to know which is which if you are coupling C and C++ files.
#include <functional>
#include <vector>
#include <cmath>
#include <numeric>
#include <iostream>


//@note If you define a free function in a header file, you should declare it as inline.
//inline vector_norm(const std::vector<double>& v){
//@note moreover this is a general utility, better be in a sparate header file than the utilities specific to the gradient descent
double vector_norm(const std::vector<double>& v){
    return std::sqrt(std::inner_product(v.cbegin(),v.cend(),v.cbegin(),0.0));
}

//@note take the habit of describe the function parameters with Doxigen type comments.
std::vector<double> gradient_method(const std::function<double(std::vector<double>)>& f,
                       const std::function<std::vector<double>(std::vector<double>)>& grad,
                       std::vector<double> x0,
                       const double tolr, const double tols,
                       double alpha, const unsigned int maxIter, const double sigma){

//@note why are you passing x0 by value? you do not need to modify it, just by a slight modification of your code, see the notes below
//      so it should be passed by const reference.
    std::vector<double> xk(x0);
    std::vector<double> x_step(x0);
    std::vector<double> grad_x0;
    bool check_step = true,check_res = true;
    unsigned int iter {0};

    while(check_step && check_res && iter<maxIter){
        ++iter;
        //@note here you can do         grad_x0 = grad(xk);

        grad_x0 = grad(x0);
        // Armijo Rule
        do{
            alpha /= 2;
            for (size_t i = 0; i != x0.size(); ++i){
                //@note here you can do 
                // x_step[i]=- alpha*grad_x0[i];
                // auto f_current = f(xk);
                // xk[i]+=x_step[i];
                xk[i] = x0[i] - alpha*grad_x0[i];
                x_step[i] = xk[i] - x0[i];
            }
            //note here you can test abs(f_current - f(xk)); So yo do not need to compute f(xk) twice
            // and you can leave x0 const as it is more logical to be.
        } while ( std::abs(f(x0)-f(xk)) <= sigma* alpha* vector_norm(grad_x0)* vector_norm(grad_x0) );

        check_step = vector_norm(x_step) > tols;
        check_res = std::abs(f(xk)-f(x0)) > tolr;
        x0 = xk;
    }
    //@note It i snot a good practive to put printouts inside function at low level like this, it is better to return 
    // the information and print it in the main function.
    // The only exception is if you are debuggingm but then it is better to enucleate the debug code with #ifdef DEBUG
    std::cout << "\nGradient Descent with Armijo Rule Completed in " << iter << " Iterations" << std::endl;

    std::cout << "Exit Condition(s):" ;
    if (!check_step) std::cout << " Step Length";
    if (!check_res) std::cout << " Residual";
    if (iter == maxIter) std::cout << " Maximum Iterations";

    return xk;
}

#endif //GRADIENTDESCENT_H
