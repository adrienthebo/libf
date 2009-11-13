/** 
 * linkedlist.h
 *
 * Implements a linear linked list
 */


/**
 * Default constructor
 *
 * Creates an empty linkedlist
 */
template<class T>
Linkedlist<T>::Linkedlist() {
    m_head = NULL;
    m_size = 0;
}
	
/**
 * Destructor
 *
 * Deallocates all memory in the linkedlist.
 */
template<class T>
Linkedlist<T>::~Linkedlist() {
    Node<T> *current_node = m_head;

    while(current_node != NULL) {
	Node<T> *next_node = current_node->next();
	
	delete current_node;

	current_node = next_node;
    }
    m_head = NULL;
}

/**
 * @param data the template data to add
 * @param position the position to add the data
 *
 * @throws list_index_out_of_bounds if position is out of bounds
 */
template<class T>
void Linkedlist<T>::add(T data, int position) throw(list_index_out_of_bounds) {
    // Bounds check
    if( position < 0 || position > m_size)
	throw list_index_out_of_bounds(position);
    

    if(m_size == 0 || position == 0) { 
	m_head = new Node<T>(data, m_head);
    }
    else {
	Node<T> *current_node = m_head;
	for(int i = 0; i + 1 < position; i++) //Locate node before insertion
	    current_node = current_node->next();
	
	current_node->next() = new Node<T>(data, current_node->next());
    }
    m_size++;
}

/**
 * Appends data to the end of the list 
 *
 * @param data the template data to add
 *
 * @throws list_index_out_of_bounds if position is out of bounds
 */
template<class T>
void Linkedlist<T>::add(T data) throw(list_index_out_of_bounds) {
    add(data, m_size);
}

/** 
 * Retrieves the node specified at position
 *
 * @param position the index of the data to retrieve
 *
 * @throws list_index_out_of_bounds if position is out of bounds
 */
template<class T>
T & Linkedlist<T>::get(int position) throw(list_index_out_of_bounds) {
    if(position < 0 || position >= m_size) 
	throw list_index_out_of_bounds(position);

    Node<T> *current_node = m_head;
    for(int i = 0; i < position; i++) {
	current_node = current_node->next();
    }
    
    if(current_node == NULL) 
	throw "Critical error; null pointer found where no null pointer should be!";

    return current_node->data();
}

/**
 * Removes the template data specified by position 
 *
 * @param position the index of the data to remove
 *
 * @throws list_index_out_of_bounds if position is out of bounds 
 */
template<class T>
void Linkedlist<T>::rm(int position) throw(list_index_out_of_bounds) {
    if(position < 0 || position >= m_size) 
	throw list_index_out_of_bounds(position);
    
    if(position == 0) {
	Node<T> *to_delete = m_head;
	m_head = to_delete->next();

	delete to_delete;
    }
    else {
	Node<T> *current_node = m_head;
	for(int i = 0; i + 1 < position; i++) {
	    current_node = current_node->next();
	}
	
	if(current_node == NULL) 
	    throw "Critical error; null pointer found where no null pointer should be!";

	Node<T> *to_delete = current_node->next();
	current_node->next() = to_delete->next();
	delete to_delete;
    }
    m_size--;
}

template<class T>
bool Linkedlist<T>::is_empty() {
    return m_size == 0;
}

template<class T>
int Linkedlist<T>::size() {
    return m_size;
}


