import java.*;
class pyramid{
    public static void main(String[] args){
        for(int i=1;i<=5;i++){
            for(int j=1;j<=5-i;j++){
                for(int z=1;z<=2*i-1;z--){
                    System.out.print(j);
                }
                System.out.println();
                    }
        }
    }
}

