
import java.util.concurrent.*;

public class Shutdown
{
	/**
	 * A static main method.
	 */ 
	public static void main(String[] args) throws InterruptedException
	{
		Runner one = new Runner();
		Thread countThread = new Thread(one , "CountThread");
		countThread.start();

		// make main thread to sleep with 1 seconds, then interrupt the countThread
		TimeUnit.SECONDS.sleep(1);
		countThread.interrupt();

		// as above described
		Runner two = new Runner();
		countThread = new Thread(two, "CountThread");
		countThread.start();

		TimeUnit.SECONDS.sleep(1);
		two.cancel();
	}

	/**
	 * A inner class that represents a thread, which be used to 
	 * demostrate cancel safety a thread using one flag or interrupted mark.
	 */ 
	private static class Runner implements Runnable
	{
		private long i;
		private volatile boolean on = true;
		
		@Override
		public void run()
		{
			while (on && !Thread.currentThread().isInterrupted())
			{
				i++;
			}
			System.out.println("Count i = " + i);
		}		

		/**
		 * Cancels this thread to stop.
		 */ 
		public void cancel()
		{
			on = false;
		}
	}
}
