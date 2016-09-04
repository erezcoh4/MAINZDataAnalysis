
# coding: utf-8

# In[16]:

import pandas as pd, matplotlib , matplotlib.pyplot as plt
#get_ipython().magic(u'matplotlib inline')


# In[17]:

dataQ21 = pd.read_csv('data/figQ21.dat', index_col=False)
#dataQ21;


# In[18]:

dataQ22 = pd.read_csv('data/figQ22.dat', index_col=False)
#dataQ22;


# In[19]:

data = dataQ22


# In[20]:

data = data[(data.bin!=0) | (data.Setup=='kin4')]


# In[21]:

#data;


# In[38]:

x = data.X
xerr = data.dX


# In[39]:

y = data.R3D / data.H
yerr = -data.dR3D / data.H


# In[40]:

xArenhovel = x
yArehnovel = data.M7 / data.H


# In[41]:

fig = plt.figure()


# In[52]:

#x,xerr,y,yerr;


# In[53]:

plt.subplot(111)
plt.scatter(xArenhovel , yArehnovel, marker='*', color='r')


# In[55]:

plt.subplot(111)
print "x: ",x
print "xerr: ",xerr
#plt.errorbar(x, y, xerr=xerr, yerr=yerr)
plt.errorbar(x, y , xerr=[xerr,xerr] , yerr = 0.1)


# In[ ]:

plt.xlabel('$\\theta_{p,q}$ [deg.]',fontsize=22)
plt.ylabel('$y-label$',fontsize=22)


# In[ ]:

ax = fig.add_subplot(111)
ax.text( 2, -0.2, "preliminary" , fontsize=30 , color='red' , alpha = 0.15 )


# In[12]:

plt.show()

