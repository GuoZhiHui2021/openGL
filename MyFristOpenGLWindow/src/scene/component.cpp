#include "component.h"
#include <common/util.h>

Component::Component(): m_entity(nullptr)
{
	m_instance_id = allocateId();
}
