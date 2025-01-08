class MinStack {
public:
	stack<int> s, s_min;
	
    MinStack() {

    }
    
    void push(int x) {
    	s.push(x);
    	if (s_min.empty()) s_min.push(x);
    	else s_min.push(min(s_min.top(), x));
    }
    
    void pop() {
    	if (!s.empty()) s.pop();
        if (!s_min.empty()) s_min.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return s_min.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */