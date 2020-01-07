function [x, flag] = ownGauss_mod(A, b)
    
    % flag = -1 -> indeterminate or incompatible
    % flag = 0 -> solvable

    [At, bt, vr, flag] = ownTriangulaion_mod(A, b);
    if flag
        [x] = backSubs_mod(At, bt, vr);
    else
        disp('Incompatible System: system not solvable')
        x = "NaN";
    end
end