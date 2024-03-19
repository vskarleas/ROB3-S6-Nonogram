function [horiz,vert] = countcell(P)
[m,n] = size(P);
horiz = zeros(m,floor(m/2));
for i = 1:m
    k = 1;
    for j = 1:n
        if P(i,j) == 0
            horiz(i,k) = horiz(i,k) + 1;  
        elseif (j>1)&& (P(i,j) == 1) && (P(i,j)~=P(i,j-1))
            k = k + 1; 
        end
    end
end
% horiz

vert = zeros(floor(n/2),n);
for j = 1:n
    k = 1;
    for i = 1:m
        if P(i,j) == 0
            vert(k,j) = vert(k,j) + 1;  
        elseif (i > 1) && (P(i,j) == 1) && (P(i,j)~=P(i-1,j))
            k = k + 1; 
        end
    end
end
% vert