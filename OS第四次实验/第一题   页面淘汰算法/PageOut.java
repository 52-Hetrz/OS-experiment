package os;

import java.util.ArrayList;
import java.util.Random;

public class PageOut {

    private ArrayList<Integer> processSequence=new ArrayList<>();       //指令序列
    private ArrayList<Integer> unDoneProcessSequence=new ArrayList<>(); //未被处理的进程序列
    private ArrayList<Integer> PageSequence=new ArrayList<>();          //内存当中的物理页
    private ArrayList<Integer> usedTime=new ArrayList<>();              //记录物理页的上一次使用时间
    private ArrayList<Integer> interruptA=new ArrayList<>();            //存储中断位 0:在内存当中 1：不在内存当中
    private int TotalPageNumber=4;                                      //内存当中分配的总的页框数
    private Random random=new Random();
    private double totalVisitTimes=0;                                   //总访问次数
    private double interruptTimes=0;                                    //缺页次数

    private PageOut(){
        for(int i=0;i<10;i++){
            interruptA.add(1);
        }
    }

    private void printPageSequence(){
        System.out.print("Now the Page in memory are :");
        for(Integer i:PageSequence){
            System.out.print(i+"   ");
        }
        System.out.print("\n");
    }

    /**
     * 产生一个待处理的指令序列
     * @param TotalProcessNumber    要产生的指令总数量
     * @param BiggestProcessNumber  最大的指令号
     */
    private void makeProcessSequence(int TotalProcessNumber,int BiggestProcessNumber){
        for(int i=0;i<TotalProcessNumber;i++){
            processSequence.add(random.nextInt(BiggestProcessNumber));
        }
        unDoneProcessSequence=processSequence;
    }

    /**
     * 根据指令查找对应的虚拟页
     * @param processNumber 指令号
     * @return  返回虚拟页的编号
     */
    private int findVirtualPage(int processNumber){

        return processNumber%10;
    }

    /**
     * FIFO算法的页面淘汰方法
     * @param Page   要查找的虚拟页
     */
    private void FIFOAlgorithm(int Page){

        {
            System.out.println(" ");
            printPageSequence();
            System.out.println("FIFO We are visiting Page " + Page);
            totalVisitTimes++;
        }

        if(interruptA.get(Page) ==1)                                    //发生缺页
        {
            System.out.println("INTERRUPT");
            interruptTimes++;
            if(PageSequence.size()<TotalPageNumber)                     //有空闲页
            {
                PageSequence.add(Page);
                interruptA.set(Page,0);
            }

            else{                                                       //没空闲页
                interruptA.set(PageSequence.get(0),1);                  //淘汰页中断位设为1
                PageSequence.remove(0);                          //执行淘汰操作
                PageSequence.add(Page);                                 //添加新页
                interruptA.set(Page,0);                                 //新页中断位设为0
            }
            printPageSequence();
        }

        else {
            System.out.print("TARGET");
        }

        System.out.println(" ");
    }

    /**
     * FIFO页面淘汰算法对一个指令序列进行操作
     * @param TotalProcessNumber    一共产生的指令数
     * @param BiggestProcessNumber  最大进程号
     */
    private void FIFO(int TotalProcessNumber,int BiggestProcessNumber){

        for(int i=0;i<10;i++){
            interruptA.add(1);
        }

        makeProcessSequence(TotalProcessNumber,BiggestProcessNumber);
        for(Integer i:processSequence){
            FIFOAlgorithm(findVirtualPage(i));
        }
        System.out.print("缺页率为："+interruptTimes/totalVisitTimes);
    }


    /**
     * 找到最长时间不会使用的页面
     * @return  返回该页面的页框号
     */
    private int findLast(){
        ArrayList<Integer> PageSequence2;
        PageSequence2=PageSequence;
        int count=0;
        for(int i:unDoneProcessSequence){
            if(PageSequence2.contains(findVirtualPage(i))){              //在未处理的指令遇到一个指令，该指令的虚拟页在内存中
                count++;
                PageSequence2.remove( (Integer) findVirtualPage(i));
            }
            if(count>=TotalPageNumber-1)
                return PageSequence2.get(0);
        }
        return PageSequence2.get(0);
    }

    /**
     * OPT算法
     * @param Page   要寻找的虚拟页
     */
    private void OPTAlgorithm(int Page){
        System.out.println(" ");
        printPageSequence();
        System.out.println("OPT We are visiting Page "+Page);
        totalVisitTimes++;
        int k;

        if(interruptA.get(Page) ==1)                                //发生缺页
        {
            System.out.println("INTERRUPT");
            interruptTimes++;
            if(PageSequence.size()<TotalPageNumber)                 //有空闲页
            {
                PageSequence.add(Page);
                interruptA.set(Page,0);
            }

            else{
                k=findLast();
                interruptA.set(k,1);                                 //没空闲页
                PageSequence.remove((Integer) k);
                PageSequence.add(Page);
                interruptA.set(Page,0);
            }
            printPageSequence();
        }

        else {
            System.out.print("TARGET");
        }

        System.out.println(" ");
    }

    /**
     * OPT页面淘汰算法对一个指令序列进行操作
     * @param TotalProcessNumber    一共产生的指令数
     * @param BiggestProcessNumber  最大进程号
     */
    private void OPT(int TotalProcessNumber,int BiggestProcessNumber){

        for(int i=0;i<10;i++){
            interruptA.add(1);
        }

        makeProcessSequence(TotalProcessNumber,BiggestProcessNumber);
        for(Integer i:processSequence){
            OPTAlgorithm(findVirtualPage(i));
        }
        System.out.print("缺页率为："+interruptTimes/totalVisitTimes);
    }


    /**
     * 使用LRU算法进行页面淘汰
     * @param Page  要访问的页
     */
    private void LRUAlgorithm(int Page){
        System.out.println(" ");
        printPageSequence();
        System.out.println("LRU We are visiting Page "+Page);
        totalVisitTimes++;

        if(interruptA.get(Page) ==1){
            System.out.println("INTERRUPT");
            interruptTimes++;
            if(PageSequence.size()<TotalPageNumber)                 //有空闲页
            {
                usedTime.add(Page);
                PageSequence.add(Page);
                interruptA.set(Page,0);
            }

            else{
                interruptA.set(usedTime.get(0),1);                  //没空闲页
                PageSequence.remove(usedTime.get(0));
                usedTime.remove(0);
                usedTime.add(Page);
                PageSequence.add(Page);
                interruptA.set(Page,0);
            }
            printPageSequence();
        }

        else {
            System.out.print("TARGET");
            usedTime.remove((Integer) Page);
            usedTime.add(Page);
        }

        System.out.println(" ");
    }

    /**
     * LRU页面淘汰算法对一个指令序列进行操作
     * @param TotalProcessNumber    一共产生的指令数
     * @param BiggestProcessNumber  最大进程号
     */
    private void LRU(int TotalProcessNumber,int BiggestProcessNumber){

        for(int i=0;i<10;i++){
            interruptA.add(1);
        }

        makeProcessSequence(TotalProcessNumber,BiggestProcessNumber);
        for(Integer i:processSequence){
            LRUAlgorithm(findVirtualPage(i));
        }
        System.out.print("缺页率为："+interruptTimes/totalVisitTimes);
    }


    /**
     * 三个页面淘汰算法的对比
     * @param TotalProcessNumber    总的指令数目
     * @param BiggestProcessNumber  最大指令号
     */
    void compare(int TotalProcessNumber,int BiggestProcessNumber){
        makeProcessSequence(TotalProcessNumber,BiggestProcessNumber);

        //FIFO
        for(int i=0;i<10;i++){
            interruptA.add(1);
        }
        for(Integer i:processSequence){
            FIFOAlgorithm(findVirtualPage(i));
        }
        System.out.println("FIFO缺页率为："+interruptTimes/totalVisitTimes);


        //LRU
        interruptA=new ArrayList<>();
        for(int i=0;i<10;i++){
            interruptA.add(1);
        }
        interruptTimes=0;
        totalVisitTimes=0;
        PageSequence=new ArrayList<>();
        for(Integer i:processSequence){
            LRUAlgorithm(findVirtualPage(i));
        }
        System.out.println("LRU缺页率为："+interruptTimes/totalVisitTimes);



        //OPT
        interruptA=new ArrayList<>();
        for(int i=0;i<10;i++){
            interruptA.add(1);
        }
        interruptTimes=0;
        totalVisitTimes=0;
        PageSequence=new ArrayList<>();
        for(Integer i:processSequence){
            OPTAlgorithm(findVirtualPage(i));
        }
        System.out.println("OPT缺页率为："+interruptTimes/totalVisitTimes);





    }

    static public void main(String[] args){
        PageOut p=new PageOut();
        p.compare(20,100);
    }
}
