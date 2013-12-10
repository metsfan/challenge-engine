#include <Challenge/Challenge.h>
#include "CollisionDetector.h"
using namespace challenge;

CollisionDetector::CollisionDetector()
{

}

void CollisionDetector::AddObject(IPhysicsObject *object)
{
	mObjects.push_back(object);
}

TCollisionDataList CollisionDetector::FindCollisions()
{
	TCollisionDataList collisionDataList;

	std::map<std::string, bool> usedMap;

	if(mObjects.size() > 0) {
		TObjectList tmpObjs(mObjects.size());
		std::copy(mObjects.begin(), mObjects.begin() + mObjects.size(), tmpObjs.begin());

		TObjectList::iterator it1 = tmpObjs.begin();
		TObjectList::iterator objEnd = tmpObjs.end();

		

		while(it1 != objEnd) {
			IPhysicsObject *object1 = (*it1);
			TObjectList::iterator it2 = tmpObjs.begin();

			while(it2 != objEnd) {
				IPhysicsObject *object2 = (*it2);

				if(object1->GetId() != object2->GetId()) {
					std::string key = object1->GetId() + ":" + object2->GetId();
					std::string key2 = object2->GetId() + ":" + object1->GetId();

					if(usedMap.count(key) == 0) {
						CollisionData *collisionData = new CollisionData();
						bool collision = object1->CollidesWith(object2, collisionData);
						if(collision) {
							for(int i = 0; i < collisionData->mContacts.size(); i++) {
								Contact *contact = collisionData->mContacts[i];
								if(object1->GetType() == kObjectTypeRigidBody && !object1->HasInfiniteMass()) {
									contact->mObjects[0] = reinterpret_cast<RigidBody *>(object1);
									if(object2->GetType() == kObjectTypeRigidBody && !object2->HasInfiniteMass()) {
										contact->mObjects[1] = reinterpret_cast<RigidBody *>(object2);
									}
								} else if(object2->GetType() == kObjectTypeRigidBody && !object2->HasInfiniteMass()) {
									contact->mObjects[0] = reinterpret_cast<RigidBody *>(object2);
								}
							}
							//object1->FireCollisionCallbacks(object2);
							//object2->FireCollisionCallbacks(object1);
							collisionDataList.push_back(collisionData);
						} else {
							delete collisionData;
						}

						usedMap[key] = true;
					} 
				}
				++it2;
			}

			++it1;
		}
	}

	return collisionDataList;
}

