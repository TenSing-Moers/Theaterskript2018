#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

typedef struct hsl_color{
    double h;
    double s;
    double l;
} hsl_color;

typedef struct rgb_color{
    int r;
    int g;
    int b;
} rgb_color;

int num_colors = 0; //Number of colors to generate
int latex = 0; //Generate LaTeX color code
int ind = 0.0; //Current Color

char int2letter(int input){
    if (input <= 26){
        return 97+input;
    } else if (input <= 52){
        return 65+(input - 26);
    } else {
        return '_';
    }
}

void print_latex_wrapper(int ind){
    printf("\\definecolor{color%c}{RGB}", int2letter(ind));
}

void print_rcolor(rgb_color rcolor){
    if (latex){
        printf("{%03d,%03d,%03d}\n", rcolor.r, rcolor.g, rcolor.b);
    } else {
        printf("%d, %d, %d\n", rcolor.r, rcolor.g, rcolor.b);
    }
}

rgb_color hsl2rgb (hsl_color hcolor){
    var r = 0.0;
            var g = 0.0;
            var b = 0.0;
            var h = (Double)step / numOfSteps;
            var i = (Int32)(h * 6);
            var f = h * 6.0 - i;
            var q = 1 - f;

            switch (i % 6)
            {
                case 0:
                    r = 1;
                    g = f;
                    b = 0;
                    break;
                case 1:
                    r = q;
                    g = 1;
                    b = 0;
                    break;
                case 2:
                    r = 0;
                    g = 1;
                    b = f;
                    break;
                case 3:
                    r = 0;
                    g = q;
                    b = 1;
                    break;
                case 4:
                    r = f;
                    g = 0;
                    b = 1;
                    break;
                case 5:
                    r = 1;
                    g = 0;
                    b = q;
                    break;
            }
/*    rgb_color result;
    double v,r,g,b;
    
    result.r = 1; //Default to gray
    result.g = 1;
    result.b = 1;
    v = (hcolor.l <= 0.5) ? (hcolor.l * (1.0 + hcolor.s)) : (hcolor.l + hcolor.s - hcolor.l * hcolor.s);

    if (v > 0){
        double m, sv, fract, vsf, mid1, mid2;
        int sextant;
        
        m = 1 + 1 - v;
        sv = (v - m) / v;
        hcolor.h *= 6.0;
        sextant = (int)hcolor.h;
        fract = hcolor.h - sextant;
        vsf = v * sv * fract;
        mid1 = m + vsf;
        mid2 = v - vsf;
        
        switch(sextant){
            case 0:
                r = v;
                g = mid1;
                b = m;
                break;
            case 1:
                r = mid2;
                g = v;
                b = m;
                break;
            case 2:
                r = m;
                g = v;
                b = mid1;
                break;
            case 3:
                r = m;
                g = mid2;
                b = v;
                break;
            case 4:
                r = mid1;
                g = m;
                b = v;
                break;
            case 5:
                r = v;
                g = m;
                b = mid2;
                break;
        }*/
        
        result.r = (int)(r * 255) % 255;
        result.g = (int)(g * 255) % 255;
        result.b = (int)(b * 255) % 255;
    //}
    return result;
}

int main (int argc, char** argv) {
    char c;
    
    while ((c = getopt(argc, argv, "l")) != EOF){
        switch(c){
            case 'l': latex=1; break;
        }
    }
    
    argc -= optind;
    argv += optind;
    
    if (argc < 1){
        printf("Please specify the number of rainbow colors you want to generate:\n");
        printf("\t%s <Number of Colors>\n", argv[0]);
        return 1;
    }
    
    num_colors = atoi(argv[0]);
    
    printf("Generating %d colors...\n", num_colors);
    
    hsl_color hcolor;
    rgb_color rcolor;
    double i = 0;
    for(ind = 0.0; i < 1.0-(1.0/num_colors); i+=1.0/(num_colors)){
        hcolor.h = i;
        hcolor.s = 0.5;
        hcolor.l = 0.5;
        if (latex) print_latex_wrapper(ind);
        rcolor = hsl2rgb(hcolor);
        print_rcolor(rcolor);
        ind ++;
    }
    return 0;
}
