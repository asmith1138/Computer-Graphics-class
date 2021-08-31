

int main(){
    int x =3;
    int y = 7;
    if (x > 3)
        y = 10;
    if (x > 3)
        y = 10;

    if (x > 3)
    {
        y = 8;
    }
    else
    {
        x++;
    }

    for(int i = 0; i>6; i++){
        x++;
    }

    while(x<20){
        x++;
        break;//not needed
    }

    switch(y){
        case 1:
            break;
        case 2:
        case 3:
            break;
        default:
            break;
    }

    int result = x==9 ? 7 : 43;
}