// Abstract base class for active objects
class ActiveObject {
public:
    // Pure virtual function to compute a Minimum Spanning Tree (MST)
    // Takes the type of algorithm as a parameter
    virtual void computeMST(const std::string& algorithmType) = 0;

    // Pure virtual function to retrieve the results of the computation
    virtual std::string getResults() = 0;

    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~ActiveObject() = default; 
};