import cvxpy as cv
import numpy as np

"""
    Calculate max return optimization with max risk tolerated used as a constraint
    returns tickers distribution in the portfolio and return rate in np.array
"""

def MarkowitzOpt(mean, variance, covariance, interest_rate, min_return, max_risk):
    n = mean.size                   # Number of assets (number of stocks + interest rate)
    mu = mean.values                    # Mean returns of n assets
    #print(mu)
    Sigma = np.zeros((n,n))                 # Covariance of n assets
    counter = 0
    for i in np.arange(n):
        for j in np.arange(i, n):
            if i==j:
                Sigma[i,j] = variance[i]
            else:
                Sigma[i,j] = covariance[counter]
                Sigma[j,i] = Sigma[i,j]
                counter += 1
    w = cv.Variable(n)                         # Portfolio allocation vector
    ret = mu.T*w
    risk = cv.quad_form(w, Sigma)
    max_risk_param = cv.Parameter()
    max_risk_param.value = max_risk
    prob = cv.Problem(cv.Maximize(ret),          # Restricting to long-only portfolio
                   [cv.sqrt(cv.sum(risk)) <= max_risk,
                    cv.sum(w) == 1,
                   w >= 0])
    prob.solve(qcp=True)
    # No solution check
    if prob.status in ["infeasible", "unbounded"]:
        return np.zeros((n+1,1))
    risk = np.dot(np.power(w.value, 2), variance.ravel().reshape((len(mu),1)))
    portfolio_and_rate = np.append(w.value, sum(w.value.T*mu))
    print(f'risk: {risk**0.5} return: {np.sum(w.value.T*mean)}')
    #print(w.value)
    return portfolio_and_rate
