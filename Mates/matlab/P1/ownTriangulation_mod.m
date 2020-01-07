function [At, bt, vr, flag] = ownTriangulation_mod(A, b)
    % Function to compute the lower triangular matrix to do Gauss
    % A=[nxn]
    % b=[nx1]
    % At: lower triangular matrix [nxn]
    % bt: modified vector [nx1]
    % vr: index vector
    % flag: 0-SI or SCI 1-SC and solvable
    
    threshHold = 1.e-6;
    vr=[];
    numUnknowns = size(A,2);
    uvr = 1:numUnknowns;
    Ab = [A, b];
    flag = 1;
    
    col = 1;
    while col <= numUnknowns-1 && flag
        [piv, maxIndex] = max(abs(Ab(uvr, col)));
        if piv < threshHold
            flag = 0;
        end
        vr = [vr, maxIndex];
        uvr = setdiff(uvr, maxIndex);
        numRows = length(uvr)*flag;
        for rowAux = 1:numRows
            row = uvr(rowAux);
            subPiv = Ab(row, col);
            Ab(row, ((col):(numUnknowns + 1))) = Ab(row, ((col):(numUnknowns+1))) - ((subPiv/piv)*Ab(maxIndex, ((col):(numUnknowns + 1))));
        end
        col = col + 1;
    end
    
    if Ab(uvr, numUnknowns) < threshHold
        flag = 0;
    end
    
    %OUTPUT
    At = Ab(:, 1:numUnknowns);
    bt = Ab(:, numUnknowns + 1);
    vr = [vr, uvr];
    
    
    %THEORY
    % TO DO
    % Aa = concatenation of A and B
    
    % TO DO
    % L = number of unknowns
    
    % TO DO
    % for loop c = from 1 until # columns -1
    % for loop r = from c+1 until #rows
    % row r = pivot*row r - subpivot* row p
    
    % TO DO
    % At = part of Aa
    % bt = part of Aa
    
    %OWN CODE
    % flag = -1 -> indeterminate or incompatible
    % flag = 0 -> solvable
    % TODO: initialise Th
    % TODO: Aa = concatenation of A and b
    % TODO: L = number of unknowns
    % TODO: Initialize vr and uvr vectors
    % TODO: create the sj vector
    % TO DO: for loop c = from 1 until # columns -1
    % TO DO: implement a function that Given Aa, sj and uvr returns
    % the abs value of the pivot and the row of the pivot
    % TO DO: Check if the returned value is under the threshold
    % TO DO: Check if the returned value is under the threshold
    % TO DO: Update the lists to remember the row pivot as visited
    % TO DO: for loop rs in uvr, modify the uvr
    % TO DO: Update the lists to remember the row pivot as visited
    % TO DO: for loop rs in uvr, modify the uvr
    % TO DO: check if the last unvisited row has a unvalid pivot nad introduce
    % the last row in the lists as visited
    % TO DO: At as part of Aa
    % TO DO: bt as part of Aa

    
    
end