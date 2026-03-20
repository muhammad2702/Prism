
#include <algorithm>
#include "Group.h"


/** Constructor for Group
 */
 Group::Group(){
    groups_.clear();
}

/** Check if the object is memeber of a specific group.
 * \param groupID Group ID which the object might have.
 * \return True if Object has Group, False if not.
 */
bool Group::hasGroup(int groupID) {


    if(groupID == -1){
        return true;
    }

     // Search for groupID in groups vector and return
    auto it = std::find (groups_.begin(), groups_.end(), groupID);

    return it != groups_.end();


}

/** Add a group to the object.
 * \param groupID ID of the Group which to add.
 */
void Group::addGroup(int groupID) {


    groups_.push_back(groupID);



}

/** Set group array, instead of single groups. ATTENTION: Clears all preexisting groups.
 * \param groups
 */
void Group::setGroups(std::vector<int> groups) {


    groups_ = std::move(groups);



}

/** Remove the Object from a single group.
 * \param groupID
 */
void Group::removeGroup(int groupID) {


    // Search groupID and delete if possible.
    auto it = std::find (groups_.begin(), groups_.end(), groupID);

    if(it != groups_.end()){

        groups_.erase(it);


    }



}

/** Remove Object from all groups it belongs to.
 */
void Group::resetGroups() {


    groups_.clear();


}

/** Get Groups of Object. Read-Only Access!
 * \return Pointer to const group vector.
 */
std::vector<int> const * Group::getGroups(){


    return &groups_;

}
