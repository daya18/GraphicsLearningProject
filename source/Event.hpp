#pragma once

template < class ...Parameters >
class Event
{
public:
	using Listener = std::function <void ( Parameters... ) >;

	void Dispatch ( Parameters const & ... ) const;
	void AddListener ( Listener );
		
private:
	std::vector <Listener> listeners;
};

// Implementation
template < class ...Parameters >
void Event<Parameters...>::Dispatch ( Parameters const & ... parameters ) const
{
	for ( auto const & listener : listeners )
		if ( listener )
			listener ( parameters... );
}

template < class ...Parameters >
void Event<Parameters...>::AddListener ( Listener listener )
{
	listeners.push_back ( listener );
}