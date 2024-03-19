function [htxt,vtxt] = maketext(H,V)

[mh,nh] = size(H);
[mv,nv] = size(V);
htxt = strings(mh,1);
vtxt = strings(nv,1);

for i = 1:mh
    for j = 1:nh
        if H(i,j) ~=0
            htxt(i) = strcat(htxt(i),num2str(H(i,j)));
            htxt(i) = strcat(htxt(i),"-");
        else
            
            continue
        end
    end
    htxt(i) = strip(htxt(i),'right','-');
end

for j = 1:nv
    for i = 1:mv
        if V(i,j) ~=0
            vtxt(j) = strcat(vtxt(j),num2str(V(i,j)));
            vtxt(j) = strcat(vtxt(j),"-");
        else
            
            continue
        end
    end
    vtxt(j) = strip(vtxt(j),'right','-');
end