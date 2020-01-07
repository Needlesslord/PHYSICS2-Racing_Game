function [x] = backSubs_mod(At, bt, vr)
    % Function to extract the solution of an upper triangular matrix
    % At=[nxn]
    % bt=[nx1]
    % vr=index vector
    % x: vector (solution)
    
    numUnknowns = length(bt);
    x = zeros(numUnknowns, 1);
    
    for iAux = numUnknowns:-1:1
        i = vr(iAux);
        sumAux = At(i, 1:numUnknowns)*x;
        x(iAux) = 1/At(i, iAux)*(bt(i)-sumAux);
    end
    
    
    % TO DO
    % L = length of b
    % prealocate the vector x in memory initialize x at 0

    % solve for the last element
    
    % loop for q = L-1 until 1
        % solve for x
        %x r = 1/diagonalTerm r * (RHS r - offdiagonalTerms {r+1:end} * ...x {r+1 to end})
    
        
        
end