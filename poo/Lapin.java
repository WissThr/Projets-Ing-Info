Lapin java;
public class Lapin{
    public int x;
    public int y;

    Lapin(int X, int Y){
        x=X;
        y=Y;
    }
    public String toString(){
        String msg="en ("+ x + ";" + y +")";
        return msg;
    }
}