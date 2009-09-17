//see problem1_2_3.PNG for the correct sigma notation of the problems
public class SigmaExamples {
	
	public int solveProblem1(){
		//calculate x^2 from 1 to 5 inclusive
		Sigma s = new Sigma(1,5){
			@Override
			public int function() {
				//implement the x^2 function
				return getCurrentIndex() * getCurrentIndex();
			}
		};
		return s.sum();
	}
	
	public int solveProblem2(){
		//calculate (-2)^i from 0 to 4 inclusive 
		Sigma s = new Sigma(0,4){
			@Override
			public int function() {
				return (int) Math.pow(-2,getCurrentIndex());
			}
		};
		return s.sum();
	}
	
	public int solveProblem3(){
		/* [view using fixed width font]
		 * 
		 * Calculate:
		 * 
		 *   n     i     j
		 * ----- ----- -----
		 *  \     \     \      /|
		 *  /     /     /       |
		 * ----- ----- ----- 
		 *  i=1   j=1   k=1
		 *  
		 *  When n = 3
		 */
		int n = 3;
		Sigma root = new Sigma(1,n);
		Sigma child1 = new Sigma(root,1,1);
		root.setChild(child1);
		Sigma child2 = new Sigma(child1,1,1){
			@Override
			public int function() {
				/*
				 * This function is a bit more complex than the previous examples.
				 * 
				 * Each child Sigma is depending on their parent currentIndex.
				 * The two lines marked a and b takes care of this
				 * 
				 * Every time this function gets called, it is because child2 gets triggered by child1 which is triggered by root.
				 */
				//set root upperBound
				/*a*/ getParent().setUpperBound( getParent().getParent().getCurrentIndex() );
				//set child upperBound
				/*b*/ setUpperBound(getParent().getCurrentIndex());
				
				//there is no other algorithm than simply to return 1
				return 1;
			}
		};
		child1.setChild(child2);
		
		//calculate sum
		return root.sum();
	}
	

	public static void main(String[]args){
		SigmaExamples ex = new SigmaExamples();
		System.out.println( "Solution to Problem1: " + ex.solveProblem1() );
		System.out.println( "Solution to Problem2: " + ex.solveProblem2() );
		System.out.println( "Solution to Problem3: " + ex.solveProblem3() );
	}
}
