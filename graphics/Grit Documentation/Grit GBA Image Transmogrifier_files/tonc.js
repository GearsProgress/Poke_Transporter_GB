//
// \file tonc.js
// \author cearn
// \date 20060505-20060505
// === NOTES ===
//

function main()
{
    id2title();
}

//! Add an appropriate title-attr to main tags with ids.
function id2title()
{
	var ii, jj, tags, id;
	var tagnames= new Array("div", "h1", "h2", "h3", "img", "pre", "table");

	for(ii in tagnames)
	{
		tags= document.getElementsByTagName(tagnames[ii]);
		for(jj in tags)
		{
			if(tags[jj].id && tags[jj].title=="")
				tags[jj].title= tags[jj].id;
		}
	}
}