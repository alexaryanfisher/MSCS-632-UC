/*Java: Garbage Collection with Corgi Splooting
Code Based on YouTube Videos and Java Tutorials:
[https://www.youtube.com/watch?v=A0LK3K4VAqc] |
[https://www.youtube.com/watch?v=Mlbyft_MFYM] | [https://www.geeksforgeeks.org/java/?ref=outind] */

public class GarbageCollection {

    static class Corgi {
        String myCorgi;

        Corgi(String myCorgi) {
            this.myCorgi = myCorgi;
            System.out.println(myCorgi + " the Corgi is born!");
        }

        void sploot() {
            System.out.println(myCorgi + " is splooting!");
        }

        @SuppressWarnings({"deprecation" })
        @Override
        protected void finalize() throws Throwable {
            //Garbage collection is processed.
            System.out.println(myCorgi + " is done splooting and is hungry.");
            super.finalize();
        }
    }
    public static void main(String[] args) {
        // Create Corgi objects
        Corgi corgi1 = new Corgi("Ein");
        Corgi corgi2 = new Corgi("Rei");
        Corgi corgi3 = new Corgi("Benni");

        // Corgis sploot
        corgi1.sploot();
        corgi2.sploot();
        corgi3.sploot();

        // Make some Corgis eligible for garbage collection by setting to null.
        corgi3 = null; // Benni is now eligible

        // Simulate some other actions
        for (int i = 0; i < 3; i++) {
            System.out.println("Looking like a loaf of bread...");
            try {
                Thread.sleep(500); //pause for 500 ms.
            } catch (InterruptedException e) {
                    e.printStackTrace();
            }
        }

        // Suggest to JVM to run garbage collection.
        System.gc();

        // Simulate thoughts while looking at corgis.
        for (int i = 0; i < 3; i++) {
            System.out.println("Oh what a cute wiggle bottom...");
            try{
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // Ein and Rei are still in scope and will be garbage collected when the program ends.
    }
}
