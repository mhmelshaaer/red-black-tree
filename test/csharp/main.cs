public class Test
{
	static void Main(string[] args)
	{
        int_rbtree T = new int_rbtree();
        T.insert(3);
        T.insert(5);
        T.insert(7);
        T.print_tree();
        T.remove(5);
        T.print_tree();
    }
}
