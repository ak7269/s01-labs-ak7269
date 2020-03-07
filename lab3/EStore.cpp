
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
    smutex_init(&mut);
    scond_init(&cond);

}

EStore::
~EStore()
{
    // TODO: Your code here.
    smutex_destroy(&mut);
    scond_destroy(&cond);
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
    smutex_lock(&mut);  
    assert(!fineModeEnabled());
    double priceItem=inventory[item_id].price+shipc;
    if(inventory[item_id].valid==false)
	    return;
    else if((inventory[item_id].valid==true)&&(inventory[item_id].quantity<1 && priceItem>budget)){
     while(inventory[item_id].quantity<1 && priceItem>budget){
	     scond_wait(&cond,&mut);
     }
       if(inventory[item_id].valid==true){
        buyItem(item_id,budget);	
       }
    }
    smutex_unlock(&mut);
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
      for(size_t i=0;i<(*item_ids).size();i++){
	Item imutex=this->inventory[(*item_ids)[i]];
	smutex_lock(&(imutex.i_lock[i]));
    }
     
    bool c=true;
    double cost=0;
    size_t i=0; 

    size_t length=(*item_ids).size();

           while(i<length){
	    Item imutex = this->inventory[(*item_ids)[i]];
	    cost+= (((imutex.price)*(1-imutex.discount))* (1-this->Dis));
	    if(imutex.quantity <= 0||!(imutex.valid) )
	    {
		    c=false;
		    break;
	    }
	    i++;
       }

       //exit f cannot run
        if( cost > budget || !c) 
	    return;

	    	for(size_t i=0;i<length;i++){
		Item imutex= this->inventory[(*item_ids)[i]];
		imutex.quantity--;//removing items
     	}

	for(size_t i=0;i<length;i++){
		Item imutex= this->inventory[(*item_ids)[i]];
		smutex_unlock(&(imutex.i_lock[i]));//mutex unlock
	}
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
    // TODO: Your code her
     smutex_lock(&mut);
      if(inventory[item_id].valid==false)
      {
    inventory[item_id].quantity=quantity;
    inventory[item_id].price=price;
    inventory[item_id].discount=discount;
    inventory[item_id].valid=true; 
      }
	if(inventory[item_id].valid==true){
	smutex_unlock(&mut);	    
	   return;
    }

     smutex_unlock(&mut);
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
    // TODO: Your code here
	  smutex_lock(&mut);

	    if(inventory[item_id].valid==false){
		smutex_unlock(&mut);

		    return;
	    }

	     inventory[item_id].quantity=0;
	     inventory[item_id].price=0.0;
	     inventory[item_id].discount=0.0;
	     inventory[item_id].valid=false;  

	     scond_signal(&cond,&mut);

	     smutex_unlock(&mut);


	     return;
	    
   
  

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
    smutex_lock(&mut);
    if(inventory[item_id].valid==true)
    {
	 inventory[item_id].quantity+=count; 
   	 smutex_unlock(&mut);
	 return;

     }
    	smutex_unlock(&mut);
        scond_signal(&cond,&mut);
      return;

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
    // TODO: Your code here.
    smutex_lock(&mut);
 
    if(inventory[item_id].valid==false)
	    return;
     
     if(price<inventory[item_id].price)
	  scond_signal(&cond,&mut);

     inventory[item_id].price=price;

        smutex_unlock(&mut);
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
    // TODO: Your code here
     smutex_lock(&mut);
     if(inventory[item_id].valid==false){
	     return;
     }
     if(inventory[item_id].discount<discount)
	     scond_signal(&cond,&mut); 

        inventory[item_id].discount=discount;

              smutex_unlock(&mut);
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
      smutex_lock(&mut);  

      
      if(cost<shipc)
	      scond_signal(&cond,&mut);
      
       shipc=cost;
	
      smutex_unlock(&mut);    
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
    smutex_lock(&mut);

    if(discount>Dis)
	    scond_signal(&cond,&mut);

    Dis=discount;

    smutex_unlock(&mut);

}
