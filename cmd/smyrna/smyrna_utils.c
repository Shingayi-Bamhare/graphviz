/* $Id$Revision: */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2004 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/
#include "smyrna_utils.h"
static int mapbool(char *p)
{
    if (p == NULL)
	return FALSE;
    if (!strcasecmp(p, "false"))
	return FALSE;
    if (!strcasecmp(p, "no"))
	return FALSE;
    if (!strcasecmp(p, "true"))
	return TRUE;
    if (!strcasecmp(p, "yes"))
	return TRUE;
    return atoi(p);
}

#if 0
static int late_int(void *obj,Agsym_t* attr, int def, int low)
{
    char *p;
    int rv;
    if (attr == NULL)
	return def;
    p = agxget(obj, attr);
    if (!p || p[0] == '\0')
	return def;
    if ((rv = atoi(p)) < low)
	rv = low;
    return rv;
}

static double late_double(void *obj, Agsym_t* attr, double def, double low)
{
    char *p;
    double rv;

    if (!attr || !obj)
	return def;
    p = agxget(obj, attr);
    if (!p || p[0] == '\0')
	return def;
    if ((rv = atof(p)) < low)
	rv = low;
    return rv;
}

static char *late_nnstring(void *obj, Agsym_t * attr, char *def)
{
    char *rv = late_string(obj, attr, def);
    if (!rv || (rv[0] == '\0'))
	rv = def;
    return rv;
}

#endif

static char* late_string(void *obj, Agsym_t * attr, char *def)
{
    if (!attr || !obj)
	return def;
    return agxget(obj, attr);
}

static int late_bool(void *obj, Agsym_t * attr, int def)
{
    if (attr == NULL)
	return def;
    return mapbool(agxget(obj, attr));
}

int l_int(void *obj, Agsym_t * attr, int def)
{
    char *p;
    if (attr == NULL)
	return def;
    p = agxget(obj, attr);
    if (!p || p[0] == '\0')
	return def;
    return atoi(p);
}

float l_float(void *obj, Agsym_t * attr, float def)
{
    char *p;
    if (!attr || !obj)
	return def;
    p = agxget(obj, attr);
    if (!p || p[0] == '\0')
	return def;
    return atof(p);
}
int getAttrBool(Agraph_t* g,void* obj,char* attr_name,int def)
{
    Agsym_t* attr;
    attr = agattr(g, AGTYPE(obj), attr_name,0);
    return late_bool(obj, attr,def);
}
int getAttrInt(Agraph_t* g,void* obj,char* attr_name,int def)
{
    Agsym_t* attr;
    attr = agattr(g, AGTYPE(obj), attr_name,0);
    return l_int(obj,attr,def);
}
float getAttrFloat(Agraph_t* g,void* obj,char* attr_name,float def)
{
    Agsym_t* attr;
    attr = agattr(g, AGTYPE(obj), attr_name,0);
    return l_float(obj,attr,def);
}
char* getAttrStr(Agraph_t* g,void* obj,char* attr_name,char* def)
{
    Agsym_t* attr;
    attr = agattr(g, AGTYPE(obj), attr_name,0);
    return late_string(obj, attr,def);
}


void setColor(glCompColor* c,GLfloat R,GLfloat G,GLfloat B,GLfloat A)
{
    c->R=R;
    c->G=G;
    c->B=B;
    c->A=A;
}
glCompPoint getPointFromStr(char* str)
{

    glCompPoint p;
    char* a;
    static char bf[512];
    strcpy(bf,str);
    p.x=0;
    p.y=0;
    p.z=0;
    a=strtok(bf,",");
    if(a)
	p.x=atof(a);
    a=strtok(NULL,",");
    if(a)
	p.y=atof(a);
    a=strtok(NULL,",");
    if(a)
	p.z=atof(a);
    return p;
}


#if 0
static float interpol(float minv, float maxv, float minc, float maxc, float x)
{
    return ((x - minv) * (maxc - minc) / (maxv - minv) + minc);
}


void 
getcolorfromschema(colorschemaset * sc, float l, float maxl,glCompColor * c)
{
    int ind;
    float percl = l / maxl * 100.00;
    for (ind = 0; ind < sc->schemacount; ind++) {
	if (percl < sc->s[ind].perc)
	    break;
    }

    if (sc->s[ind].smooth) {
	c->R =
	    interpol(sc->s[ind - 1].perc, sc->s[ind].perc,
		     sc->s[ind - 1].c.R, sc->s[ind].c.R, percl);
	c->G =
	    interpol(sc->s[ind - 1].perc, sc->s[ind].perc,
		     sc->s[ind - 1].c.G, sc->s[ind].c.G, percl);
	c->B =
	    interpol(sc->s[ind - 1].perc, sc->s[ind].perc,
		     sc->s[ind - 1].c.B, sc->s[ind].c.B, percl);
	c->A = 1;
    } else {
	c->R = sc->s[ind].c.R;
	c->G = sc->s[ind].c.G;
	c->B = sc->s[ind].c.B;
	c->A = 1;
    }
}
#endif
