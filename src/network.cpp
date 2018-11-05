#include "network.h"
#include <vector>
#include "random.h"
#include <iostream>

using namespace std;
bool already_nodes(multimap< size_t, size_t> map, const size_t& a, const size_t& b);

void Network::resize(const size_t& t)
	{
		vector<double> tab(t);
		RandomNumbers Rn;
		Rn.normal(tab);
		values = tab;
	}

bool Network::add_link(const size_t& a, const size_t& b)
	{
		if((a >= values.size()) or (b >= values.size()) or(a ==b) or already_nodes(links, a, b)) 
		{ 
			//cerr << "ERROR : Unsuitable index of nodes" << endl;
			return false;
		}
		
		links.insert(pair<size_t, size_t>(a, b));
		links.insert(pair<size_t, size_t>(b, a));
		
		return true;
	}

size_t Network::random_connect(const double& mean_deg)
	{
		RandomNumbers Rn;
		
		multimap<size_t, size_t>::iterator it;
		for(it = links.begin(); it !=links.end(); ++it)
			{ links.erase(it);}
		
		links.clear();
		
		
		for(size_t n(0); n < values.size(); ++ n)
			{
				
				size_t degree_n(RNG.poisson(mean_deg));
				size_t i(0);
				int diff(degree_n - degree(n));
				
				if(diff > 0)
				{
					vector<size_t> nodes_to_link;
					RNG.uniform_int(nodes_to_link, 0, (values.size()-1));
					while( i < diff)
						{ 
							if(add_link(n, nod_to_link))
								{ 
									++i; 
								}
						}
				}
			}
		return (links.size()/2);
			
	}
	
bool already_nodes(multimap<size_t, size_t> map, const size_t& a, const size_t& b)
	{
		//trouver sil existe deja des couples a,b et b,a 
		pair <multimap<size_t, size_t>::iterator, multimap<size_t, size_t>::iterator> ref(map.equal_range(a));

		for( multimap<size_t, size_t>::iterator it=ref.first; it!=ref.second; ++it)
			{
				if(it->second == b)
					{ return true; }
			}
		
		return false;
	}

size_t Network::set_values(const vector<double>& tab)
	{
		for(size_t i(0); i < min(values.size(), tab.size()); ++i)
			{
				values[i] = tab[i];
			}
			
		return (min(values.size(), tab.size()));

	}

size_t Network::size() const
{
	return values.size();
}

size_t Network::degree(const size_t& n) const
	{
			return links.count(n);
	}
 
double Network::value(const size_t& n) const
	{
		if(n < values.size() )
		{
			return values[n];
		}
		 return 0;
	}

vector<double> Network::sorted_values() const
	{
		vector<double> tab (values);
		sort(tab.begin(), tab.end(), greater<double>());
		return tab;
	}

vector<size_t> Network::neighbors(const size_t& n) const
	{
		multimap<size_t, size_t> map = links;
		vector<size_t> neighbours;
		pair <multimap<size_t, size_t>::iterator, multimap<size_t, size_t>::iterator> ref(map.equal_range(n));
		
		for(multimap<size_t, size_t>::iterator raf=ref.first; raf != ref.second; ++raf)
			{
				neighbours.push_back(raf->second);
			}
			
		return neighbours;
	}
