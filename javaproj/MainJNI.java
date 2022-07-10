public class MainJNI {

	public static void main(String[] args) 
	{
		JNICAsyncSocket casyncsocket = new JNICAsyncSocket();
		System.out.println("Created casyncsocket using filedescriptor " + casyncsocket.getSocket());
	}

}
