    #include <iostream>
    #include <unordered_map>

    using namespace std;

    class FibonacciCache {
    public:
        FibonacciCache(int max_size) : max_size(max_size) {}

        int get(int key) {
            auto it = cache.find(key);
            return (it != cache.end()) ? it->second : -1; // Return -1 if key not found
        }

        void put(int key, int value) {
            if (cache.size() >= max_size) {
                evict();
            }
            cache[key] = value;
        }

    private:
        void evict() {
            if (!cache.empty()) {
                auto it = cache.begin();
                cache.erase(it); // Simple eviction: remove the first item
            }
        }

        int max_size;
        std::unordered_map<int, int> cache;
    };

    int fibonacciWithCache(int n, FibonacciCache& cache) {
        if (n <= 1) {
            return n;
        }

        int cachedResult = cache.get(n);
        if (cachedResult != -1) {
            return cachedResult;
        }

        int result = fibonacciWithCache(n - 1, cache) + fibonacciWithCache(n - 2, cache);

        cache.put(n, result);

        return result;
    }

    int calculateNthFibonacci(int n, int maxCacheSize) {
        FibonacciCache cache(maxCacheSize);
        return fibonacciWithCache(n, cache);
    }

    int main() {
        
        int n;
        cout << "Enter the desired value of n: ";
        cin >> n;

    
        int maxCacheSize;
        cout << "Enter the desired cache size: ";
        cin >> maxCacheSize;


        int result = calculateNthFibonacci(n, maxCacheSize);

        std::cout << "The " << n << "th Fibonacci number is: " << result << std::endl;

        return 0;
    }
