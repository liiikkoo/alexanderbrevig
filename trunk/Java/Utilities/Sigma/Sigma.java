/**
 * <code>Sigma.java</code>
 * 
 * <p>This is a class for implementing summation operator algorithms with JAVA</p>
 * 
 * <p>It is <b>important</b> that one of the <code>Sigma</code>s overrides the <code>int function()</code> method. </p>
 * <p>This is what makes the <code>Sigma</code> class work.</p>
 * 
 * @version 1.0
 * @author Alexander Brevig
 *
 */
public class Sigma {
	
	private int currentIndex;
	private int lowerBound;
	private int upperBound;
	private int sum;
	private Sigma parent; //the controlling sigma
	private Sigma child;  //the exploited sigma

	/**
	 * <p>Create a root </code>Sigma</code></p>
	 * @param lowerBound <p>The lower bound for this <code>Sigma</code></p>
	 * @param upperBound <p>The upper bound for this <code>Sigma</code></p>
	 */
	public Sigma(int lowerBound, int upperBound){
		this(null, lowerBound, upperBound, null);
	}
	/**
	 * <p>Create a node </code>Sigma</code></p>
	 * @param parent <p>The parent <code>Sigma</code></p>
	 * @param lowerBound <p>The lower bound for this <code>Sigma</code></p>
	 * @param upperBound <p>The upper bound for this <code>Sigma</code></p>
	 */
	public Sigma(Sigma parent, int lowerBound, int upperBound){
		this(parent, lowerBound, upperBound, null);
	}
	
	/**
	 * <p><code>Sigma</code> constructor.</p>
	 * @param parent <p>The parent <code>Sigma</code></p>
	 * @param lowerBound <p>The lower bound for this <code>Sigma</code></p>
	 * @param upperBound <p>The upper bound for this <code>Sigma</code></p>
	 * @param child <p>The child <code>Sigma</code></p>
	 */
	public Sigma(Sigma parent, int lowerBound, int upperBound, Sigma child){
		this.parent = parent;
		this.upperBound = upperBound;
		this.lowerBound = lowerBound;
		this.child = child;
		this.currentIndex = this.lowerBound;
	}
	
	/**
	 * Calculate the sum
	 * @return the calculated sum
	 */
	public int sum(){	
		sum = 0;	
		
		for (int i=lowerBound; i<=upperBound; i++){
			this.currentIndex = i;
			if (child!=null){
				sum += child.sum();
			}else{
				sum += function();
			}
		}
		
		return sum;
	}
	
	/**
	 * Calculate the sum using a nested summation operator
	 * @param s the child to use when calculating
	 * @return the calculated sum
	 */
	public int sum(Sigma s){
		int sum = 0;
		for (int i=lowerBound; i<=upperBound; i++){
			sum += 1;//s.sum(i);
		}
		return sum;
	}

	public int getSum() { return sum; }
	public void setSum(int sum) { this.sum = sum; }
	public Sigma getParent() { return parent; }
	public Sigma getChild() { return child; }
	
	public int getCurrentIndex() { return currentIndex; }
	public int getUpperBound() { return upperBound; }
	public int getLowerBound() { return lowerBound; }

	public void setUpperBound( int upperBound ) { this.upperBound = upperBound; }
	public void setLowerBound( int lowerBound ) { this.lowerBound = lowerBound; }
	
	/**
	 * <p>This will set the <code>child</code> of this <code>Sigma</code></p>
	 * @param child <p>The new <code>child</code></p>
	 */
	public void setChild( Sigma child ) { this.child = child; }
	
	/**
	 * <p>The function this <code>Sigma</code> will execute each iteration in the summation loop</p>
	 * <p>Remember to implement this in such a manner that it modifies the parent <code>Sigma</code>s appropriately</p>
	 * @return <p>The result of the function</p>
	 */
	public int function() { return -1; }
}
