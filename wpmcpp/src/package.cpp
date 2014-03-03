#include "package.h"

#include "xmlutils.h"

int Package::indexOf(const QList<Package*> pvs, Package* f)
{
    int r = -1;
    for (int i = 0; i < pvs.count(); i++) {
        Package* pv = pvs.at(i);
        if (pv->name == f->name) {
            r = i;
            break;
        }
    }
    return r;
}

bool Package::contains(const QList<Package*> &list, Package *pv)
{
    return indexOf(list, pv) >= 0;
}

Package::Package(const QString& name, const QString& title)
{
    this->name = name;
    this->title = title;
}

QString Package::getShortName() const
{
    QString r;
    int index = this->name.lastIndexOf('.');
    if (index < 0)
        r = this->name;
    else
        r = this->name.mid(index + 1);
    return r;
}

bool Package::isValidName(const QString& name)
{
    bool r = false;
    if (!name.isEmpty() && !name.contains(" ") && !name.contains("..")) {
        r = true;
    }
    return r;
}

void Package::saveTo(QDomElement& e) const {
    e.setAttribute("name", name);
    XMLUtils::addTextTag(e, "title", title);
    if (!this->url.isEmpty())
        XMLUtils::addTextTag(e, "url", this->url);
    if (!description.isEmpty())
        XMLUtils::addTextTag(e, "description", description);
    if (!this->icon.isEmpty())
        XMLUtils::addTextTag(e, "icon", this->icon);
    if (!this->license.isEmpty())
        XMLUtils::addTextTag(e, "license", this->license);
    for (int i = 0; i < this->categories.count(); i++) {
        XMLUtils::addTextTag(e, "category", this->categories.at(i));
    }
}

Package *Package::clone() const
{
    Package* np = new Package(this->name, this->title);
    np->url = this->url;
    np->icon = this->icon;
    np->description = this->description;
    np->license = this->license;
    np->categories = this->categories;

    return np;
}