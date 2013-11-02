/*************************************************************************
 * Copyright © 2011-2013 Kévin Lesénéchal <kevin@lesenechal.org>         *
 *                                                                       *
 * This file is part of WebCpp, see <http://www.webcpp.org/>.            *
 *                                                                       *
 * WebCpp is free software: you can redistribute it and/or modify it     *
 * under the terms of the GNU General Public License as published by the *
 * Free Software Foundation, either version 3 of the License, or (at     *
 * your option) any later version.                                       *
 *                                                                       *
 * WebCpp is distributed in the hope that it will be useful, but WITHOUT *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or *
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License  *
 * for more details.                                                     *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with WebCpp. If not, see <http://www.gnu.org/licenses/>.        *
 *************************************************************************/

/**
 * @file CompiledTpl.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-20
 */

#ifndef _WPP_COMPILEDTPL_H_
#define _WPP_COMPILEDTPL_H_

#include <MVC/Templates/AbstractCompiledTemplate.h>

class Path;
class Block;

class CompiledTpl : public AbstractCompiledTemplate
{
public:
	CompiledTpl(const Path& filePath);

	virtual ~CompiledTpl();

	/**
	 * @brief Renders the compiled template
	 * @param tpl The template instance to render
	 * @return The output
	 */
	virtual String render(Template* tpl) override;

	/**
	 * @brief Get the template's root block
	 */
	Block* rootBlock() const;

	/**
	 * @brief Set the template's root block
	 * @param rootBlock The new root block
	 */
	void setRootBlock(Block* rootBlock);

private:
	/**
	 * @brief The template's root block
	 */
	Block* _rootBlock;
};

#endif // !_WPP_COMPILEDTPL_H_
