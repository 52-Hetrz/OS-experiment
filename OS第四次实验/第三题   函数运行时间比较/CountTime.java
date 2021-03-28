package os;

public class CountTime {

    int[][] a=new int[50][50];

    CountTime(int time){
        Long startTime,endTime;
        int m=0;
        for(;m<5;m++) {
            startTime = System.currentTimeMillis();
            for (int i = 0; i < time; i++)
                for (int j = 0; j < 50; j++)
                    for (int k = 0; k < 50; k++)
                        a[j][k] = m;
            endTime = System.currentTimeMillis();
            System.out.print("先行后列 ：" + (endTime - startTime)+"\n");

            startTime = System.currentTimeMillis();
            for (int i = 0; i < time; i++)
                for (int j = 0; j < 50; j++)
                    for (int k = 0; k < 50; k++)
                        a[k][j] = m;
            endTime = System.currentTimeMillis();
            System.out.print("先列后行 ：" + (endTime - startTime)+"\n\n");

        }
    }

    static public void main(String[] args){
        CountTime c=new CountTime(50000);
    }
}
