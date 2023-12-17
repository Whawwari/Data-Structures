Name: Waleed hawwari

ID:1153191


External resources used:
I used the given websites from the extra help class, they are really benefical with learning concepts.
Gribbleab
W3School
geekforgeeks
tutorialspoint
Alot of youtube

State of the current implementation
I believe the functionality of my code works, although sadly there is a segmentation error that i just cant seem to fix.

### Hash Tables:

**Strengths:**
- **Fast Operations**: Hash tables offer O(1) average time complexity for key-based operations like search, insert, and delete, making them extremely fast for data retrieval.
- **Memory Efficiency**: They only allocate memory necessary for the elements stored, which can be more efficient compared to other data structures.
- **Scalability**: Hash tables handle large numbers of entries efficiently, maintaining performance even as the dataset grows.
- **Flexible Key Types**: They support a wide range of data types as keys, as long as a suitable hash function is available.
- **Direct Data Access**: Hash tables allow for immediate access to data if the key is known, bypassing the need for sequential search.
- **Handles Duplicates**: While keys must be unique, hash tables can store multiple entries with duplicate values.
- **Dynamic Resizing**: Many implementations resize dynamically, maintaining efficiency as the amount of data changes.
- **Ideal for Caching**: Their quick lookup capabilities make them excellent for caching applications.
- **Efficient Algorithms**: Hash tables support efficient algorithms for tasks like deduplication, grouping, and fast lookups.
- **Collision Resolution**: They have established methods for handling collisions, such as chaining and open addressing.
- **Widely Used**: As a fundamental data structure, they are widely used and understood, with extensive support in literature and libraries.

**Weaknesses:**
- **Collision Handling**: Performance can degrade if many keys hash to the same index, leading to time complexity degradation in worst-case scenarios.
- **Memory Overhead**: Some implementations, especially those with dynamic resizing and collision handling, can have higher memory overhead.
- **Unordered**: Hash tables do not maintain any order of elements, which can be a drawback when order is important.
- **Hash Function Dependency**: The efficiency of a hash table is highly dependent on the quality of the hash function used.
- **Immutable Keys**: Once a key-value pair is inserted, the key cannot be modified; it must be removed and reinserted with a new key.

### Tries:

**Strengths:**
- **Prefix Searching**: Tries are extremely efficient for operations involving prefixes, such as autocomplete features.
- **Sorted Data**: They inherently store keys in a sorted manner, which is beneficial for applications requiring ordered data.
- **No Collisions**: Unlike hash tables, tries do not suffer from key collisions.
- **Flexible Key Length**: Tries can accommodate keys of varying lengths without any performance degradation.
- **Predictable Performance**: Their performance is generally consistent and does not depend on factors like hash functions.
- **Space Efficient for Overlapping Keys**: Tries are space-efficient when the dataset contains many overlapping prefixes, as common prefixes are shared.

**Weaknesses:**
- **Space Consumption**: For datasets with few overlapping prefixes, tries can consume more space due to the storage of nodes and pointers.
- **Slower Operations**: For non-prefix-based searches, tries can be slower than hash tables.
- **Complexity**: Tries are more complex to implement and understand compared to simpler data structures like hash tables.

### Conditions for Choosing Hash Table:

**Required Conditions:**
- **Rapid Key-Based Operations**: When the primary requirement is fast access, insertion, and deletion based on keys.
- **Immutable and Hashable Keys**: The keys used must be suitable for hashing and remain unchanged once inserted.

**Preferred Conditions:**
- **No Need for Ordering**: When the order of elements is not a concern.
- **Datasets with Few Overlapping Prefixes**: Ideal when the data does not involve common prefixes, as hash tables do not benefit from such structures.

### Conditions for Choosing Trie:

**Required Conditions:**
- **Efficient Prefix Searching**: Essential for applications like autocomplete where prefix-based search is a core functionality.
- **Variable Length or String Keys**: When keys are strings or have variable lengths, tries are particularly well-suited.

**Preferred Conditions:**
- **Datasets with Many Overlapping Prefixes**: Tries are ideal when the dataset contains many common prefixes, as they can store such data more efficiently.
- **Requirement for Sorted Keys**: When there is a need to maintain keys in a sorted order, tries inherently provide this feature.
