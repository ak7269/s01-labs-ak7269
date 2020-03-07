#include <cassert>

#include "EStore.h"
#include <cstdio>
using namespace std;


Item::
Item() : valid(false)
{
}

Item::
~Item()
{
}


EStore::
EStore(bool enableFineMode)
    : fineMode(enableFineMode)
{
    // TODO: Your code here.
    smutex_init(&m);
    scond_init(&c);
  
}

EStore::
~EStore()
 {
    // TODO: Your code here.
    //
   smutex_destroy(&m);
   scond_destroy(&c);

}

/*
 * ------------------------------------------------------------------
 * buyItem --
 *
 *      Attempt to buy the item from the store.
 *
 *      An item can be bought if:
 *          - The store carries it.
 *          - The item is in stock.
 *          - The cost of the item plus the cost of shipping is no
 *            more than the budget.
 *
 *      If the store *does not* carry this item, simply return and
 *      do nothing. Do not attempt to buy the item.
 *
 *      If the store *does* carry the item, but it is not in stock
 *      or its cost is over budget, block until both conditions are
 *      met (at which point the item should be bought) or the store
 *      removes the item from sale (at which point this method
 *      returns).
 *
 *      The overall cost of a purchase for a single item is defined
 *      as the current cost of the item times 1 - the store
 *      discount, plus the flat overall store shipping fee.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void EStore::
buyItem(int item_id, double budget)
{

	double purchaseprice=inventory[item_id].price+storeshipping;
    assert(!fineModeEnabled());

    // TODO: Your code here.
    //
    smutex_lock(&m);
	if(inventory[item_id].valid==false)
	{
		return;
	}
	else{
		if(inventory[item_id].quantity<=0 || purchaseprice>budget)
		{
		while(inventory[item_id].quantity>0 && purchaseprice<=budget)
		{
			scond_wait(&c,&m);
		}
		}
		if(inventory[item_id].valid==true)
		{
			buyItem(item_id,budget);
		}

	

	}
	smutex_unlock(&m);
	return;


 }

/*
 * ------------------------------------------------------------------
 * buyManyItem --
 *
 *      Attempt to buy all of the specified items at once. If the
 *      order cannot be bought, give up and return without buying
 *      anything. Otherwise buy the entire order at once.
 *
 *      The entire order can be bought if:
 *          - The store carries all items.
 *          - All items are in stock.
 *          - The cost of the the entire order (cost of items plus
 *            shipping for each item) is no more than the budget.
 *
 *      If multiple customers are attempting to buy at the same
 *      time and their orders are mutually exclusive (i.e., the
 *      two customers are not trying to buy any of the same items),
 *      then their orders must be processed at the same time.
 *
 *      For the purposes of this lab, it is OK for the store
 *      discount and shipping cost to change while an order is being
 *      processed.
 *
 *      The cost of a purchase of many items is the sum of the
 *      costs of purchasing each item individually. The purchase
 *      cost of an individual item is covered above in the
 *      description of buyItem.
 *
 *      Challenge: For bonus points, implement a version of this
 *      method that will wait until the order can be fulfilled
 *      instead of giving up. The implementation should be efficient
 *      in that it should not wake up threads unecessarily. For
 *      instance, if an item decreases in price, only threads that
 *      are waiting to buy an order that includes that item should be
 *      signaled (though all such threads should be signaled).
 *
 *      Challenge: For bonus points, ensure that the shipping cost
 *      and store discount does not change while processing an
 *      order.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void EStore::
buyManyItems(vector<int>* item_ids, double budget)
{
    assert(fineModeEnabled());
	
    // TODO: Your code here.
//	for(size_t i=0;i<(*item_ids).size();i++)
//	{
//		Item curr=this->inventory[(*item_ids)[i]];
//		smutex_lock(&(curr.itemLock));
//		printf("%d ", (*item_ids)[i]);


	
//	}
//	printf("\n");
//	bool buyable=true;
//	double total_cost=0;
//	for(size_t i=0;i<(*item_ids).size();i++)
//	{
//		Item curr= this->inventory[(*item_ids)[i]];
//		total_cost+= (((curr.price)*(1-curr.discount))* (1-this->discountcost));
//		if(!(curr.valid) || curr.quantity <= 0){
//			buyable=false;
//			break;
//		}
		
				
//	}
//	if(!buyable || total_cost>budget) {
		return;
//	}
//	for(size_t i=0;i<(*item_ids).size();i++)
//	{
//		Item curr= this->inventory[(*item_ids)[i]];
//		(curr.quantity)--;

				
//	}
//	for(size_t i=0;i<(*item_ids).size();i++)
//	{
//		Item curr= this->inventory[(*item_ids)[i]];
//		smutex_unlock(&(curr.itemLock));

				
//	}



}

/*
 * ------------------------------------------------------------------
 * addItem --
 *
 *      Add the item to the store with the specified quantity,
 *      price, and discount. If the store already carries an item
 *      with the specified id, do nothing.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void EStore::
addItem(int item_id, int quantity, double price, double discount)
{
    // TODO: Your code here.
    //
    //
    	smutex_lock(&m);
	if(inventory[item_id].valid==true)
	{
		return;
	}


	inventory[item_id].price=price;
	inventory[item_id].quantity=quantity;
	inventory[item_id].discount=discount;
	inventory[item_id].valid=true;
	smutex_unlock(&m);


}

/*
 * ------------------------------------------------------------------
 * removeItem --
 *
 *      Remove the item from the store. The store no longer carries
 *      this item. If the store is not carrying this item, do
 *      nothing.
 *
 *      Wake any waiters.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void EStore::
removeItem(int item_id)
{
    // TODO: Your code here.
    //
   smutex_lock(&m);
  // int f=0;
  //  for(int i=0;i<INVENTORY_SIZE;i++)
  //  {
//	if(i==item_id)
//		f=1;


 //   }
   if(inventory[item_id].valid==false)
    {
	return;
    }

	inventory[item_id].price=0.0;
	inventory[item_id].quantity=0;
	inventory[item_id].discount=0.0;
	inventory[item_id].valid=false;

	scond_signal(&c,&m);
	smutex_unlock(&m);

}

/*
 * ------------------------------------------------------------------
 * addStock --
 *
 *      Increase the stock of the specified item by count. If the
 *      store does not carry the item, do nothing. Wake any waiters.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void EStore::
addStock(int item_id, int count)
{
    // TODO: Your code here.
    smutex_lock(&m);
    if(inventory[item_id].valid==false){
      scond_signal(&c,&m);
      return;
    }
    inventory[item_id].quantity+=count;
    smutex_unlock(&m);
}

/*
 * ------------------------------------------------------------------
 * priceItem --
 *
 *      Change the price on the item. If the store does not carry
 *      the item, do nothing.
 *
 *      If the item price decreased, wake any waiters.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void EStore::
priceItem(int item_id, double price)
{
smutex_lock(&m);
// int f=0;

 //   for(int i=0;i<INVENTORY_SIZE;i++)
   // {
//	if(i==item_id)
//		f=1;


  //  }
    //if(f==0)
   // {
//	return;
  //  }
  if(inventory[item_id].valid==false)
	  return;
  if(price<inventory[item_id].price)
  {
	  scond_signal(&c,&m);
  }
	inventory[item_id].price=price;

smutex_unlock(&m);
   // TODO: Your code here.

}

/*
 * -----------------------------------------------------------------
 * discountItem --
 *
 *      Change the discount on the item. If the store does not carry
 *      the item, do nothing.
 *
 *      If the item discount increased, wake any waiters.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void EStore::
discountItem(int item_id, double discount)
{
    // TODO: Your code here.
    smutex_lock(&m);
 if(inventory[item_id].valid==false){
             return;
     }
     if(inventory[item_id].discount<discount)
             scond_signal(&c,&m);

       //smutex_lock(&m);
       inventory[item_id].discount=discount;
       smutex_unlock(&m);
}

/*
 * ------------------------------------------------------------------
 * setShippingCost --
 *
 *      Set the per-item shipping cost. If the shipping cost
 *      decreased, wake any waiters.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void EStore::
setShippingCost(double cost)
{
    // TODO: Your code here.
//int i;
//	for(i=0;i<INVENTORY_SIZE;i++)
//	{
//	inventory[i].storeshipping=cost;	
//	}
	smutex_lock(&m);
 	storeshipping=cost;
	
	if(cost<storeshipping)
		scond_signal(&c,&m);


	smutex_unlock(&m);
}

/*
 * ------------------------------------------------------------------
 * setStoreDiscount --
 *
 *      Set the store discount. If the discount increased, wake any
 *      waiters.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void EStore::
setStoreDiscount(double discount)
{
    // TODO: Your code here.
 smutex_lock(&m);
    if(discount>discountcost)
            scond_signal(&c,&m);
    discountcost=discount;
    smutex_unlock(&m);
}


