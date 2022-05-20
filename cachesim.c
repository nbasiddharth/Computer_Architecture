#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 

struct cacheline{
    long add;
    int boffset;
    long setindexA;
    long tagA;
    int age;
    int valid;
    char choice;

};

struct prefcacheline{
    long add;
    int boffset;
    long setindexA;
    long tagA;
    int age;
    int valid;
    char choice;
};

long prefetch(long add, long bl){
    
    long carry;
    while (bl != 0){
      carry = add & bl;
      add = add ^ bl;
      bl = carry << 1;
    }

    return add;

}

int main (int argc, char **argv){
    int csize;
    int bsize;
    int result;
    int bresult;
    int sets;
    int lines;
    
    csize = atoi(argv[1]);
    bsize = atoi(argv[4]);

    result = strcmp(argv[2], "direct");
    bresult = strcmp(argv[2], "assoc");

    if(result == 0){
        sets = csize/bsize;
        lines = 1;
    }
    else if(bresult == 0){
        sets = 1;
        lines = csize/bsize;
    }
    else{
        int endword;
        endword = 6;
        while(argv[2][endword] != '\0'){
            endword = endword +1;
        }
        char* num = (char*)malloc(((endword-6)+1) * sizeof(char));
        int tick;
        int z;
        z = 6;
        for(tick = 0; tick < ((endword -6)+1); tick++){
            num[tick] = argv[2][z+tick];
            
        }
        int n;
        n = atoi(num);
        sets = csize/(bsize*n);
        lines = n;
        free(num);
    }   
    
    long blockbits;
    int bit;
    int tempA;
    tempA = bsize;
    bit = 0;
    while(bsize >> 1 != 0){
        bit = bit+1;
        bsize = bsize >> 1;
    }
    blockbits = bit;
    bsize = tempA;

    long setbits;
    int tempB;
    tempB = sets;
    bit = 0;
    while(sets >> 1 != 0){
        bit = bit+1;
        sets = sets >> 1;
    }
    setbits = bit;
    sets = tempB;

    long tagbits = 48 - blockbits - setbits;
   
    FILE *actual = fopen(argv[5], "r");
    
    //Constructing a cache
    int i;
    struct cacheline ** cache = malloc((sets+1) * sizeof(struct cacheline *)); 
    for (i = 0; i < (sets+1) ; ++i) {
        cache[i] = malloc(lines * sizeof(struct cacheline)); 
    }


    //Constructing a prefetch cache
    int nex;
    struct prefcacheline ** ncache = malloc((sets+1) * sizeof(struct prefcacheline *)); 
    for (nex = 0; nex < (sets+1) ; ++nex) {
        ncache[nex] = malloc(lines * sizeof(struct prefcacheline)); 
    }

    //filling cache up with random values
    int x = 0;
    int y = 0;
    for (x = 0; x < sets; x++){
        for(y = 0; y < lines; y++){
            cache[x][y].add = 0;
            cache[x][y].age = 0;
            cache[x][y].boffset = 0;
            cache[x][y].setindexA = x;
            cache[x][y].tagA = -999;
            cache[x][y].valid = 0;
            cache[x][y].choice = 'a';
        }
    }

    int x01 = 0;
    int y01 = 0;
    for (x01 = 0; x01 < sets; x01++){
        for(y01 = 0; y01 < lines; y01++){
            ncache[x01][y01].add = 0;
            ncache[x01][y01].age = 0;
            ncache[x01][y01].boffset = 0;
            ncache[x01][y01].setindexA = x;
            ncache[x01][y01].tagA = -999;
            ncache[x01][y01].valid = 0;
            ncache[x01][y01].choice = 'a';
        }
    }

    
    
    //Reading and Writing Cache data
    char action;
    long unsigned address;
    //char check[BUFSIZ];
    //char b;
    char a[BUFSIZ];
    long blockoffset;
    long setindex;
    long tag;
    int count;
    int hits;
    int target;
    hits = 0;
    target = 0;
    int misses;
    misses =0;
    long bv = 1;
    int rw;
    int reads;
    reads = 0;
    int writes;
    writes = 0;
    //int rwcheck;




    int preftarget;
    int prefhits;
    prefhits = 0;
    //int prefrwcheck;
    int prefmisses;
    prefmisses = 0;
    int prefreads;
    prefreads = 0;
    int prefwrites;
    prefwrites = 0;
    

    fscanf(actual, "%s %c %lx", a, &action, &address);
    
    
    while(fscanf(actual, "%[^\n]", a) != EOF){
       blockoffset = address & ((1 << blockbits)-1);
       setindex = (address >> blockbits) & ((1 << setbits) -1);
       tag = ((address >> (blockbits+setbits)) & ((bv << tagbits) -bv));

     
       target = 0; 
       preftarget = 0;
       if(action == 'R'){
           rw = 1;
       }
       else {
           rw = 0;
       }
       //Checking hits on normal cache
       for(count = 0; count < lines; count++){
           if(cache[setindex][count].valid == 1){
                if(tag == cache[setindex][count].tagA){
                    hits = hits + 1;
                    //rwcheck = count;
                    target = target + 1;
                    
                }
            }
        }
        //Checking hits on prefcache
        count = 0;
        for(count = 0; count < lines; count++){
            if(ncache[setindex][count].valid == 1){
                if(tag == ncache[setindex][count].tagA){
                    prefhits = prefhits +1;
                    //prefrwcheck = count;
                    preftarget = 1;
                }
            }
        }


        
       
        int track;
        int place;
        place = 0;
        int spot;
        spot = 0;
        int maxage;
        maxage = 0;
        int maxindex;
        maxindex = 0;

        
        
         //If there was no hit, placing address into normal cache 
        if(target == 0){
            if(rw == 1){
                reads = reads +1;
            }
            else{
                reads = reads +1;
                writes = writes +1;
            }
            
            misses = misses +1;
            for(track = 0; track < lines; track++){
                if(cache[setindex][track].valid == 1 ){
                    if(cache[setindex][track].age >= maxage){
                        maxage = cache[setindex][track].age;
                        maxindex = track; 
                    }
                    cache[setindex][track].age = cache[setindex][track].age +1;
                }
                else{
                    spot = 1;
                    place = track;
                    
                }
                
            }

            if(spot == 1){
                cache[setindex][place].add = address;
                cache[setindex][place].age = 0;
                cache[setindex][place].setindexA = setindex;
                cache[setindex][place].valid = 1;
                cache[setindex][place].boffset = blockoffset;
                cache[setindex][place].tagA = tag;
                cache[setindex][place].choice = action;
                
            
            }
            else{
                cache[setindex][maxindex].add = address;
                cache[setindex][maxindex].age = 0;
                cache[setindex][maxindex].setindexA = setindex;
                cache[setindex][maxindex].valid = 1;
                cache[setindex][maxindex].boffset = blockoffset;
                cache[setindex][maxindex].tagA = tag;
                cache[setindex][maxindex].choice = action;
            }
        }
        //Noting reads and writes if there has been a hit for normal cache
        else{
            if(action == 'W'){
                writes = writes +1;

            }
                
            
        }
        int preftrack;
        int prefplace;
        prefplace = 0;
        int prefspot;
        prefspot = 0;
        int prefmaxage;
        prefmaxage = 0;
        int prefmaxindex;
        prefmaxindex = 0;
        //If there has been no hit, placing address into prefcache
        if(preftarget == 0){
            if(rw == 1){
                prefreads = prefreads +1;
            }
            else{
                prefreads = prefreads +1;
                prefwrites = prefwrites +1;
            }
            
            prefmisses = prefmisses +1;
            for(preftrack = 0; preftrack < lines; preftrack++){
                if(ncache[setindex][preftrack].valid == 1 ){
                    if(ncache[setindex][preftrack].age >= prefmaxage){
                        prefmaxage = ncache[setindex][preftrack].age;
                        prefmaxindex = preftrack; 
                    }
                    ncache[setindex][preftrack].age = ncache[setindex][preftrack].age +1;
                }
                else{
                    prefspot = 1;
                    prefplace = preftrack;
                    
                }
                
            }

            if(prefspot == 1){
                ncache[setindex][prefplace].add = address;
                ncache[setindex][prefplace].age = 0;
                ncache[setindex][prefplace].setindexA = setindex;
                ncache[setindex][prefplace].valid = 1;
                ncache[setindex][prefplace].boffset = blockoffset;
                ncache[setindex][prefplace].tagA = tag;
                ncache[setindex][prefplace].choice = action;
                
            
            }
            else{
                ncache[setindex][prefmaxindex].add = address;
                ncache[setindex][prefmaxindex].age = 0;
                ncache[setindex][prefmaxindex].setindexA = setindex;
                ncache[setindex][prefmaxindex].valid = 1;
                ncache[setindex][prefmaxindex].boffset = blockoffset;
                ncache[setindex][prefmaxindex].tagA = tag;
                ncache[setindex][prefmaxindex].choice = action;
            }
        }

        //Noting reads and writes if there has been a hit for prefetch cache
        else{
            if(action == 'W'){
                prefwrites = prefwrites +1;
            }
        }
        // Prefetching For prefetch cache misses
        long next;
        long prefblock;
        long prefset;
        long preftg;
        long tb;
        tb = 1;

        int p;
        int pmaxage;
        pmaxage = 0;
        int pmaxindex;
        pmaxindex = 0;
        int pspot;
        pspot = 0;
        int pplace;

        int pcnt;
        int noprefetch;
        noprefetch = 0;

        if(preftarget == 0){
            next = prefetch(address,bsize);
            prefblock = next & ((1 << blockbits)-1);
            prefset = (next >> blockbits) & ((1 << setbits) -1);
            preftg = ((next >> (blockbits+setbits)) & ((tb << tagbits) -tb));

           

            pcnt = 0;
            for(pcnt = 0; pcnt < lines; pcnt++){
                if(ncache[prefset][pcnt].valid == 1){
                    if(preftg == ncache[prefset][pcnt].tagA){
                        noprefetch = 1;
                    }
                }
            }

            if(noprefetch == 0){
                prefreads = prefreads + 1;
                for(p = 0; p < lines; p++){
                    if(ncache[prefset][p].valid == 1 ){
                        if(ncache[prefset][p].age >= pmaxage){
                            pmaxage = ncache[prefset][p].age;
                            pmaxindex = p; 
                        }
                      ncache[prefset][p].age = ncache[prefset][p].age +1;
                    }
                    else{
                        pspot = 1;
                        pplace = p;
                    
                    }
                }
                if(pspot == 1){
                    ncache[prefset][pplace].add = next;
                    ncache[prefset][pplace].age = 0;
                    ncache[prefset][pplace].setindexA = prefset;
                    ncache[prefset][pplace].valid = 1;
                    ncache[prefset][pplace].boffset = prefblock;
                    ncache[prefset][pplace].tagA = preftg;
                    ncache[prefset][pplace].choice = 'R';
                
            
                }
                else{
                    ncache[prefset][pmaxindex].add = next;
                    ncache[prefset][pmaxindex].age = 0;
                    ncache[prefset][pmaxindex].setindexA = prefset;
                    ncache[prefset][pmaxindex].valid = 1;
                    ncache[prefset][pmaxindex].boffset = prefblock;
                    ncache[prefset][pmaxindex].tagA = preftg;
                    ncache[prefset][pmaxindex].choice = 'R';
                }
        
        
        
        
            }
        }

        //printf("%lx  %lx\n", ncache[0][0].add, ncache[0][1].add);
        
        fscanf(actual, "%s %c %lx", a, &action, &address);
        if(strcmp(a,"#eof") == 0){
            break;
        }
    }



printf("Prefetch %d\n", 0);
printf("Memory reads: %d\n", reads);
printf("Memory writes: %d\n", writes);
printf("Cache hits: %d\n", hits);
printf("Cache misses: %d\n", misses);
printf("Prefetch %d\n", 1);
printf("Memory reads: %d\n", prefreads);
printf("Memory writes: %d\n", prefwrites);
printf("Cache hits: %d\n", prefhits);
printf("Cache misses: %d\n", prefmisses);

     
    
    //Freeing normal cache
    int close;
    for(close = 0; close < (sets+1); ++close){
        free(cache[close]);
    }
    free(cache);

    //Freeing prefetch cache
    int freedom;
    for(freedom = 0; freedom < (sets+1); ++freedom){
        free(ncache[freedom]);
    }
    free(ncache);
    return 0;


}
/*
0x804ae19: R 0x9cb3d40
0x804ae19: W 0x9cb3d40
0x804ae1c: R 0x9cb3d44
0x804ae1c: W 0x9cb3d44
0x804ae10: R 0xbf8ef498
*/